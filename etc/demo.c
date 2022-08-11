/* 
 * _DEMO_C_
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
// #include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h> // Crucial for sleeping on macOS

// ---------------------------------- FUNC2
void func2(){
  fprintf(stdout, "I am odd!\n");
  fflush(stdout);
}

// ---------------------------------- FUNC1
void func1(){
  fprintf(stdout, "I am even!\n");
  fflush(stdout);
}

// ---------------------------------- MAIN FUNCTION
int main( int argc, char **argv ){

  printf("Starting...\n");
  sleep(2);
 
  func1();
 
  sleep(2);
  printf("Ending!\n");
  
  return 0;
}
/* ================================== EOF ================================== */
