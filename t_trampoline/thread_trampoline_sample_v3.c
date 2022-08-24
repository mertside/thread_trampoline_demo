/* _THREAD_TRAMPOLINE_SAMPLE_C_
 *
 * Version 3 - 2022/07/16
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#include <unistd.h> // for macOS

// ---------------------------------- MACROS
#define NUM_THREADS 8

// ---------------------------------- GLOBAL VARIABLES
// `thread_ptr` stores the jump pointers for each thread
volatile uint64_t thread_ptr[NUM_THREADS];

// `thread_id` will store our thread id's from pthread_create
pthread_t thread_id[NUM_THREADS];

// ---------------------------------- FUNC3
void func3(){
  printf( "FUNC3: I am another function!\n" );
}

// ---------------------------------- FUNC2
void func2(){
  printf( "FUNC2\n" );
}

// ---------------------------------- FUNC1
void func1(){
  printf( "FUNC1\n" );
}

// ---------------------------------- SPINWAIT FUNCTION
void *spinWait(void *arg){
  uint64_t *localPtr = (uint64_t *)(arg);
  volatile uint64_t Val = 0x00ull;
  void (*Func)() = NULL;

  Val = localPtr[0];
  while( Val == 0x00ull ){
    // spinwait
    Val = 0x00ull;
    sleep(1);
  }

  // Val is no longer zero
  printf( "Val is no longer zero!\n" );

  // That means someone told us where to jump to
  Func = (void (*)(void *))Val;

  // Jump to the user-defined function
  (*Func)();
}

// ---------------------------------- MAIN FUNCTION
int main( int argc, char **argv ){

  // can take number of threads as args
  int numOfThreads = NUM_THREADS;
  if(argc > 1) {
    numOfThreads = atoi(argv[1]);
  }

  int i = 0;
  int err = 0;

  // initialize all thread pointers to 0x00
  for( i=0; i<numOfThreads; i++ ){
    thread_ptr[i] = 0x00ull;
  }

  // create the threads
  for( i=0; i<numOfThreads; i++ ){
    err = pthread_create(&thread_id[i], NULL, spinWait, &thread_ptr[i]);
  }

  // tell each thread to jump to a specific function
  // -- even threads jump to Func1
  for( i=0; i<numOfThreads; i+=2 ){
    // printf( "I am even: %d\n", i );
    thread_ptr[i] = &func1;
  }
  
  // -- even threads jump to Func2
  for( i=1; i<numOfThreads; i+=2 ){
    // printf( "I am odd : %d\n", i );
    thread_ptr[i] = &func2;
  }
  
  /*
  sleep(1);
  if( numOfThreads>=2 ) {
    thread_ptr[0] = &func3;
  }
  */
  //thread_ptr[1] = &func3;

  // close the threads
  for( i=0; i<numOfThreads; i++ ){
    err = pthread_join(thread_id[i], NULL);
  }

  return 0;
}

/* EOF */
