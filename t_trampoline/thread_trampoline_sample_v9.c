/* 
 * _THREAD_TRAMPOLINE_SAMPLE_C_
 *
 * Version 9 - 2022/08/08
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> // Crucial for sleeping on macOS

// -------------------------------------------------------------------- MACROS
#define DEBUG 1
#define MAX_NUM_OF_THREADS 16
//#define MAX_NUM_LENGTH 10

// ------------------------------------------------------------------- STRUCTS
typedef struct args{
  uint64_t thread_id;
  volatile uint64_t trampoline_memory;
} args;

typedef enum {false, true} bool;

// ---------------------------------------------------------- GLOBAL VARIABLES
// Handles for each thread thread
pthread_t thread_handles[MAX_NUM_OF_THREADS];

// Args struct for each thread
args thread_args[MAX_NUM_OF_THREADS];

// Indicates whether threads are done
volatile bool done = false;

// --------------------------------------------------------------------- FUNC2
void func2(){
  fprintf(stdout, "I am odd!\n");
  fflush(stdout);
}

// --------------------------------------------------------------------- FUNC1
void func1(){
  fprintf(stdout, "I am even!\n");
  fflush(stdout);
}

// ------------------------------------------------------ ENDSPINWAIT FUNCTION
/*
void endSpinWait(){
#if DEBUG
  printf("Thread's work is done!\n");
#endif
  // This thread's work is done
  pthread_exit(NULL);
}
*/

// --------------------------------------------------------- SPINWAIT FUNCTION
void *spinWait( void *arg ){

  args *thread_args = (args*)(arg);
  uint64_t my_id = thread_args->thread_id;
  volatile uint64_t *my_trampoline = &(thread_args->trampoline_memory);
  
  // Loop to spinWait (...sleep;jump;sleep...)
  while(!done){  
    // Function pointer for redirection
    void (*Func)() = NULL;

    // Do nothing until trampoline address is set
    while((*my_trampoline) == 0x00ull){
      sleep(1);
    }

    // Someone loaded an address into the trampoline
#if DEBUG
    fprintf(stdout, "\t[*] Thread %lu: Trampoline at address %p set to %p!\n", 
           my_id, (void *) my_trampoline, (void *) *my_trampoline);
#endif

    // Check condition to end spinWait loop
    if((*my_trampoline) == 0xdeadbeef){ 
#if DEBUG
      fprintf(stdout, "\t[*] Thread %lu: My work is done!\n", my_id);
#endif
      // Break out of the loop 
      done = true; // break; 
    } else {
      // Cast the address to a function pointer
      Func = (void (*)(void *))(*my_trampoline);

      // Jump to the user-defined function
      (*Func)();

      // Reset the trampoline address
      *my_trampoline = 0x00ull; // thread_args->trampoline_memory = 0x00ull;

#if DEBUG
      fprintf(stdout, "\t[*] Thread %lu: Trampoline at address %p REset %p!\n", 
             my_id, (void *) my_trampoline, (void *) *my_trampoline);
#endif
    
    }
  } // END of infinite while
 
  fflush(stdout); 
  // This thread's work is done
  pthread_exit(NULL);
}

// ------------------------------------------------------------- MAIN FUNCTION
int main( int argc, char **argv ){

  int i = 0;
  int numOfThreads = MAX_NUM_OF_THREADS; 
  
  // Can take number of threads as args
  if(argc > 1){                                                                 
    numOfThreads = atoi(argv[1]);                                               
  } else { 
    // Get number of threads from the environment 
    //char *str = malloc( sizeof(char) * MAX_NUM_LENGTH );
    //str = getenv("NUM_OF_THREADS");
    //char str[MAX_NUM_LENGTH];
    //strcpy(str, getenv("NUM_OF_THREADS"));
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

  //putenv("NUM_OF_THREADS=2"); // "NUM_OF_THREADS=8"
  //numOfThreads=atoi(getenv("NUM_OF_THREADS"));

#if DEBUG  
  fprintf(stdout, "\nNumber of threads: %d\n", numOfThreads);
  fflush(stdout);  
#endif

  // initialize thread args
  for( i=0; i<numOfThreads; i++ ){
    thread_args[i].thread_id = i;
    thread_args[i].trampoline_memory = 0x00ull;
  }

#if DEBUG
  fprintf(stdout, "\nAddresses of trampolines: \n");
  for(i = 0; i< numOfThreads; i++){
    fprintf(stdout, "Thread %lu: %p\t", thread_args[i].thread_id, 
           &(thread_args[i].trampoline_memory));
  }
  fprintf(stdout, "\n");
  fprintf(stdout, "\nValues of trampolines: \n");
  for(i = 0; i< numOfThreads; i++){
    fprintf(stdout, "Thread %lu: %p\t", thread_args[i].thread_id, 
           (void *) thread_args[i].trampoline_memory);
  }
  fprintf(stdout, "\n");
  fprintf(stdout, "\nAddresses of Functions - \tFunc1: %p \tFunc2: %p\n", 
         &func1, &func2);
  // printf("\nAddresses of EndSpinWait: %p\n", &endSpinWait);
#endif
  
  fflush(stdout);
  //sleep(2);
  //printf("\n");

  // create the threads
  for(i=0; i<numOfThreads; i++){
    pthread_create(&thread_handles[i], NULL, spinWait, &thread_args[i]);
  }

  fflush(stdout);
  //sleep(2);
  //printf("\n");

  // tell each thread to jump to a specific function
  // -- even threads jump to Func1
  for(i=0; i<numOfThreads; i+=2){
    thread_args[i].trampoline_memory = (uint64_t) &func1;
#if DEBUG
    fprintf(stdout, "    Thread %lu trampoline set to %p\n", 
            thread_args[i].thread_id,(void *)thread_args[i].trampoline_memory);
#endif
  }
 
  fflush(stdout); 
  //sleep(2);
  //printf("\n");

  // -- odd threads jump to Func2
  for(i=1; i<numOfThreads; i+=2){
    thread_args[i].trampoline_memory = (uint64_t) &func2;
#if DEBUG
    fprintf(stdout, "    Thread %lu trampoline set to %p\n", 
            thread_args[i].thread_id,(void *)thread_args[i].trampoline_memory);
#endif
  }

  fflush(stdout);
  sleep(2); // FIXME:HACK: Without sleep Func1 and Func2 does NOT execute
  //printf("\n");

  // -- all threads end spinWait
  for(i=0; i<numOfThreads; i++){
    // Pass a specific address to end spinWait
    thread_args[i].trampoline_memory = (uint64_t) 0xdeadbeef;
    // Jump to a specific function to end spinWait
    // thread_args[i].trampoline_memory = (uint64_t) &endSpinWait;
#if DEBUG
  fprintf(stdout, "    Thread %lu trampoline set to %p for completion\n", 
          thread_args[i].thread_id, (void *) thread_args[i].trampoline_memory);
#endif
  }
  
  fflush(stdout);
  //sleep(2);
  //printf("\n");

  // close the threads
  for(i=0; i<numOfThreads; i++){
    pthread_join(thread_handles[i], NULL);
  }

  //sleep(2);
  printf("\n");

  return 0;
}
/* ================================== EOF ================================== */
