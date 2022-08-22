/*                                                                              
 * _TPOOL_H_                                                       
 *
 * on 2022/08/22                                                       
 *                                                                              
 */   
#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <stdbool.h>
#include <stddef.h>

// ---------------------------------------------------------------- PROTOTYPES
struct tpool;
typedef struct tpool tpool_t;

typedef void (*thread_func_t)(void *arg);

tpool_t *tpool_create(size_t num);
void tpool_destroy(tpool_t *tm);

// Adds work to the queue for processing. 
bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg);

// Blocks until all work has been completed.
void tpool_wait(tpool_t *tm);

// --------------------------------------------------------------- OBJECT DATA

// Simple linked list which stores the function to call and its arguments.
struct tpool_work {
  thread_func_t      func;
  void              *arg;
  struct tpool_work *next;
};
typedef struct tpool_work tpool_work_t;

struct tpool {
  tpool_work_t    *work_first;    // used for push/pop
  tpool_work_t    *work_last;     // used for push/pop
  pthread_mutex_t  work_mutex;    // single mutex for all locking
  pthread_cond_t   work_cond;     // signal threads; there is work to process
  pthread_cond_t   working_cond;  // signal; no threads processing
  size_t           working_cnt;   // number of threads actively processing work
  size_t           thread_cnt;    // number of threads alive 
  bool             stop;          // stops the threads
};

// ---------------------------------- Simple helper for creating work objects.
static tpool_work_t *tpool_work_create(thread_func_t func, void *arg)
{
  tpool_work_t *work;

  if (func == NULL)
    return NULL;

  work       = malloc(sizeof(*work));
  work->func = func;
  work->arg  = arg;
  work->next = NULL;
  return work;
}

// -------------------------------- Simple helper for destroying work objects. 
static void tpool_work_destroy(tpool_work_t *work)
{
  if (work == NULL)
    return;
  free(work);
}

// --------------------------------------------------------- GET WORK FUNCTION
// Handles pulling an object from the list and 
//   maintain the list work_first and work_last references.
static tpool_work_t *tpool_work_get(tpool_t *tm)
{
  tpool_work_t *work;

  if (tm == NULL)
    return NULL;

  work = tm->work_first;
  if (work == NULL)
    return NULL;

  if (work->next == NULL) {
    tm->work_first = NULL;
    tm->work_last  = NULL;
  } else {
    tm->work_first = work->next;
  }

  return work;
}

// ----------------------------------------------------------- WORKER FUNCTION
// At a high level: this function waits for work and processes it.
static void *tpool_worker(void *arg)
{
  tpool_t      *tm = arg;
  tpool_work_t *work;

  // This will keep the tread running until exit.
  while (1) {
    // Locking the mutex so nothing manipulates the pool’s members.
    pthread_mutex_lock(&(tm->work_mutex));

    // Check if any work available for processing.
    while (tm->work_first == NULL && !tm->stop)
      pthread_cond_wait(&(tm->work_cond), &(tm->work_mutex));

    // Check if the pool has requested that all threads stop and exit.
    if (tm->stop)
      break;
    // The thread was signaled there is work.
    work = tpool_work_get(tm);
    tm->working_cnt++;
    pthread_mutex_unlock(&(tm->work_mutex));

    // If there was work, process it and destroy the work object.
    if (work != NULL) {
      work->func(work->arg);
      tpool_work_destroy(work);
    }

    // The work has been processed.
    pthread_mutex_lock(&(tm->work_mutex));
    tm->working_cnt--;
    if (!tm->stop && tm->working_cnt == 0 && tm->work_first == NULL)
      pthread_cond_signal(&(tm->working_cond));
    pthread_mutex_unlock(&(tm->work_mutex));
  }

  // Arrival from break out.
  tm->thread_cnt--;
  pthread_cond_signal(&(tm->working_cond));
  pthread_mutex_unlock(&(tm->work_mutex));
  return NULL;
}

// ------------------------------------------------------ POOL CREATE FUNCTION
tpool_t *tpool_create(size_t num)
{
  tpool_t   *tm;
  pthread_t  thread;
  size_t     i;
  
  // The minumum acceptable number of threads is two threads. 
  if (num == 0)
    num = 2;
  // XXX:IDEA: May set the number of core/processors + 1 as the default...

  tm             = calloc(1, sizeof(*tm));
  tm->thread_cnt = num;

  pthread_mutex_init(&(tm->work_mutex), NULL);
  pthread_cond_init(&(tm->work_cond), NULL);
  pthread_cond_init(&(tm->working_cond), NULL);

  tm->work_first = NULL;
  tm->work_last  = NULL;

  // The requested threads are started and tpool_worker is specified.
  for (i=0; i<num; i++) {
    // Start num of threads; tpool_worker is specified as the thread function.
    pthread_create(&thread, NULL, tpool_worker, tm);
    // XXX: Did NOT store the thread ids; they are not accessed directly.
    //      If we wanted to implement some kind of force exit, 
    //      instead of having to wait then we’d need to track the ids.
    pthread_detach(thread);
  }

  return tm;
}

// ----------------------------------------------------- POOL DESTROY FUNCTION
void tpool_destroy(tpool_t *tm)
{
  tpool_work_t *work;
  tpool_work_t *work2;

  if (tm == NULL)
    return;

  // Throwing away all pending work; caller BEWARE!!!
  pthread_mutex_lock(&(tm->work_mutex));
  work = tm->work_first;
  while (work != NULL) {
    work2 = work->next;
    tpool_work_destroy(work);
    work = work2;
  }

  // Cleaned up the queue; tell the threads they need to stop.
  tm->stop = true;
  pthread_cond_broadcast(&(tm->work_cond));
  pthread_mutex_unlock(&(tm->work_mutex));

  // Wait for the processing threads to finish. 
  tpool_wait(tm);

  pthread_mutex_destroy(&(tm->work_mutex));
  pthread_cond_destroy(&(tm->work_cond));
  pthread_cond_destroy(&(tm->working_cond));

  free(tm);
}

// -------------------------------------------------- Adding work to the queue
bool tpool_add_work(tpool_t *tm, thread_func_t func, void *arg)
{
  tpool_work_t *work;

  if (tm == NULL)
    return false;
  
  // Creating a work object. 
  work = tpool_work_create(func, arg);
  if (work == NULL)
    return false;

  pthread_mutex_lock(&(tm->work_mutex));
  // Adding the object to the liked list. 
  if (tm->work_first == NULL) {
    tm->work_first = work;
    tm->work_last  = tm->work_first;
  } else {
    tm->work_last->next = work;
    tm->work_last       = work;
  }

  pthread_cond_broadcast(&(tm->work_cond));
  pthread_mutex_unlock(&(tm->work_mutex));

  return true;
}

// ---------------------------------------- Waiting for processing to complete
void tpool_wait(tpool_t *tm)
{
  if (tm == NULL) // Will only return when there is no work. 
    return;

  pthread_mutex_lock(&(tm->work_mutex));
  while (1) {
    if ((!tm->stop && tm->working_cnt != 0) || 
        (tm->stop && tm->thread_cnt != 0)) {
      pthread_cond_wait(&(tm->working_cond), &(tm->work_mutex));
    } else {
      break;
    }
  }
  pthread_mutex_unlock(&(tm->work_mutex));
}

#endif /* __TPOOL_H__ */
