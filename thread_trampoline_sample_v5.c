/* _THREAD_TRAMPOLINE_SAMPLE_C_
 *
 * Version 4 - 2022/07/18
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#include <unistd.h> // for macOS

// ---------------------------------- MACROS
#define DEBUG 1
#define NUM_THREADS 8

// ---------------------------------- STRUCTS
typedef struct args{
  uint64_t thread_id;
  volatile uint64_t trampoline_memory;
} args;

// ---------------------------------- GLOBAL VARIABLES
// Handles for each thread thread
pthread_t thread_handles[NUM_THREADS];

// Args struct for each thread
args thread_args[NUM_THREADS];

// ---------------------------------- FUNC2
void func2(){
  printf("I am odd!\n");
}

// ---------------------------------- FUNC1
void func1(){
  printf("I am even!\n");
}

// ---------------------------------- SPINWAIT FUNCTION
void *spinWait(void *arg){

  args *thread_args = (args*)(arg);
  uint64_t my_id = thread_args->thread_id;
  volatile uint64_t *my_trampoline = &(thread_args->trampoline_memory);
  
  // Function pointer for redirection
  void (*Func)() = NULL;

  // Do nothing until trampoline address is set
  while((*my_trampoline) == 0x00ull){
    sleep(1);
  }

  // Someone loaded an address into the trampoline
#if DEBUG
  printf("\t[*] Thread %lu: Trampoline at address %p set to %p!\n", my_id, my_trampoline, *my_trampoline);
#endif

  // Cast the address to a function pointer
  Func = (void (*)(void *))(*my_trampoline);

  // Jump to the user-defined function
  (*Func)();

  // This thread's work is done
  pthread_exit(NULL);
}

// ---------------------------------- MAIN FUNCTION
int main( int argc, char **argv ){

  int i = 0;
    
  // can take number of threads as args
  int numOfThreads = NUM_THREADS;
  if(argc > 1) {
    numOfThreads = atoi(argv[1]);
  }


  // initialize thread args
  for(i=0; i<numOfThreads; i++){
    thread_args[i].thread_id = i;
    thread_args[i].trampoline_memory = 0x00ull;
  }

#if DEBUG
  printf("\nAddresses of trampolines: \n");
  for(i = 0; i< numOfThreads; i++){
    printf("Thread %lu: %p\t", thread_args[i].thread_id, &(thread_args[i].trampoline_memory));
  }
  printf("\n");
  printf("\nValues of trampolines: \n");
  for(i = 0; i< numOfThreads; i++){
    printf("Thread %lu: %p\t", thread_args[i].thread_id, thread_args[i].trampoline_memory);
  }
  printf("\n");
  printf("\nAddresses of Functions - Func1: %p Func2: %p\n", &func1, &func2);
#endif

  // create the threads
  for( i=0; i<numOfThreads; i++ ){
    pthread_create(&thread_handles[i], NULL, spinWait, &thread_args[i]);
  }

  // tell each thread to jump to a specific function
  // -- even threads jump to Func1
  for( i=0; i<numOfThreads; i+=2 ){
    thread_args[i].trampoline_memory = (uint64_t) &func1;
#if DEBUG
    printf("\tThread %lu trampoline set to %p\n", thread_args[i].thread_id, thread_args[i].trampoline_memory);
#endif
  }
  
  // -- odd threads jump to Func2
  for( i=1; i<numOfThreads; i+=2 ){
    thread_args[i].trampoline_memory = (uint64_t) &func2;
#if DEBUG
    printf("\tThread %lu trampoline set to %p\n", thread_args[i].thread_id, thread_args[i].trampoline_memory);
#endif
  }
  
  printf("\n");

  // close the threads
  for(i=0; i<numOfThreads; i++ ){
    pthread_join(thread_handles[i], NULL);
  }

  return 0;
}
/* EOF */
