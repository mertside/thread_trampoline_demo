/* 
 * _THREAD_POOL_SAMPLE_C_
 *
 * by Mert SIDE <mert.side@ttu.edu> 
 *
 * Version 3 - 2022/08/28
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "threadpool.h"

// -------------------------------------------------------------------- MACROS  
#define DEBUG 1                                                                 
#define MAX_NUM_OF_THREADS 16   

// ---------------------------------------------------------- GLOBAL VARIABLES
//static const size_t num_threads = 4;
//static const size_t num_items   = 10;

// --------------------------------------------------------------------- FUNC2  
void func2()
{                                                                     
  fprintf(stdout, "I am func2!\n");                                               
  fflush(stdout);
  sleep(1);                                                               
}                                                                               
                                                                                
// --------------------------------------------------------------------- FUNC1  
void func1()
{                                                                     
  fprintf(stdout, "I am func1!\n");                                              
  fflush(stdout);                                                               
  sleep(1);
} 

// ------------------------------------------------------------- MAIN FUNCTION
int main(int argc, char **argv)
{   
  int i = 0;                                                                    
  int numOfThreads = MAX_NUM_OF_THREADS;                                        
                                                                                
  // Can take number of threads as args                                         
  if(argc > 1){                                                                 
    numOfThreads = atoi(argv[1]);                                               
  } else {                                                                      
    // Get number of threads from the environment                               
    char *str = getenv("NUM_OF_THREADS");                                       
    // Is the environment variable set appropriately?                           
    if(str == NULL || atoi(str) <= 0 || atoi(str) > MAX_NUM_OF_THREADS){        
      if(str == NULL) {                                                         
        // NOT found!                                                           
        fprintf(stderr, "\nNUM_OF_THREADS not set; set environment first!\n");  
      } else {                                                                  
        // NOT a reasonable number!                                             
        fprintf(stderr, "\nNUM_OF_THREADS should be between %d and %d\n",       
                1, MAX_NUM_OF_THREADS);                                         
      }                                                                         
      // Set MAX number of threads as an environment variable                   
      const char *envName = "NUM_OF_THREADS";                                    
      char envValue[10] = "";                                                   
      sprintf(envValue, "%d", numOfThreads);                                     
      setenv(envName, envValue, 1);                                   
    }                                                                           
    numOfThreads = atoi(getenv("NUM_OF_THREADS"));                              
    //free(str);                                                                
  }    

#if DEBUG                                                                       
  fprintf(stdout, "\nNumber of threads: %d\n", numOfThreads);                   
  fflush(stdout);                                                               
#endif  

  tpool_work_queue_t *pool;
  pool = tpool_create(numOfThreads);   

  // tell each thread to jump to a specific function                            
  // -- jump to Func1                                              
  for(i=0; i<numOfThreads; i+=1){                                               
    tpool_add_work(pool, func1, NULL);     
#if DEBUG                                                                       
    fprintf(stdout, "    Executing Func1\n");                       
#endif 
  } 
  // -- sleep 
  sleep(1); 
  int sleepTimer = 5;                                                          
  for(i=0; i<sleepTimer; i+=1){                                               
#if DEBUG                                                                       
    fprintf(stdout, "    Sleeping for %d seconds\n", (sleepTimer-i));                                   
#endif        
    sleep(1);                                                   
  }      
  // -- jump to Func2                                               
  for(i=0; i<numOfThreads; i+=1){ 
    tpool_add_work(pool, func2, NULL);  
#if DEBUG                                                                       
    fprintf(stdout, "    Executing Func2\n");                    
#endif 
  }  

  //fflush(stdout);                                                               
  //sleep(2); // FIXME:HACK: Without sleep Func1 and Func2 does NOT execute       
  //printf("\n"); 

  // Will return when there is no work
  tpool_wait(pool);

  // Discard pending, clean queue, order stop, wait, destroy
  tpool_destroy(pool); 

  return 0;
}

/* ================================== EOF ================================== */
