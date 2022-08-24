/* 
 * _THREAD_POOL_SAMPLE_C_
 *
 * Adapted from the work of John Schember <john@nachtimwald.com>:               
 *   https://nachtimwald.com/2019/04/12/thread-pool-in-c/                       
 * by Mert SIDE <mert.side@ttu.edu> 
 *
 * Version 1 - 2022/08/22
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "threadpool.h"

// ---------------------------------------------------------- GLOBAL VARIABLES
static const size_t num_threads = 4;
static const size_t num_items   = 10;

// ----------------------------------------------------------- WORKER FUNCTION 
void worker(void *arg)
{
  int *val = arg;
  int  old = *val;

  // Take an int pointer add 1000.
  *val += 1000;
  // Print the values before and after the operation.
  printf("tid=%p, old=%d, val=%d\n", (void *)pthread_self(), old, *val);

  // Try and get the threads to run in a non-linear order.
  if (*val%2)
    usleep(100000);
  // A fast enough system will have each thread finish one after another;
  //   making it appear as if threads aren’t being used (that’s a good thing).
}

// ------------------------------------------------------------- MAIN FUNCTION
int main(int argc, char **argv)
{
  tpool_t *tm;
  int     *vals;
  size_t   i;

  tm   = tpool_create(num_threads);
  // Create an array of 100 ints and add them as work to the queue. 
  vals = calloc(num_items, sizeof(*vals));

  // Go through some work items using a few threads for fun.
  for (i=0; i<num_items; i++) {
    vals[i] = i;
    tpool_add_work(tm, worker, vals+i);
  }

  tpool_wait(tm);

  for (i=0; i<num_items; i++) {
    printf("Value #%d is %d\n", (int)i, vals[i]);
  }

  free(vals);
  tpool_destroy(tm);
  return 0;
}

/* ================================== EOF ================================== */
