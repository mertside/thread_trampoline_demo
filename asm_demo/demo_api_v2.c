 /*
  * _DEMO_API_C_
  *
  */

//#include "xbrtime.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#define _ALLOC_SIZE_ 8

// ------------------------------------------------------- FUNCTION PROTOTYPES
void __xbrtime_asm_fence();
void __xbrtime_asm_quiet_fence();

void __xbrtime_get_u8_seq(uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                          uint32_t nelems, uint32_t stride );
void __xbrtime_put_u8_seq(uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                          uint32_t nelems, uint32_t stride );


// ------------------------------------------------------------------ ASSEMBLY
/*
__asm__ __volatile__ ( "...;"
                       "...;" 
                      : ... );
  add a1, a1, a4
  bne x31,a3,.get_u8_seq
  ret
*/

// ----------------------------------------------------------- U8 GET FUNCTION
void xbrtime_ulonglong_get(unsigned long long *dest, const unsigned long long *src,
                     size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else if( (stride != 1) || (nelems == 1)){
    /* sequential execution */
    __xbrtime_get_u8_seq(src,//__xbrtime_ltor((uint64_t)(src),pe),
                         (uint64_t)(dest),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }
  //__xbrtime_asm_fence();
}

// ----------------------------------------------------------- U8 PUT FUNCTION
void xbrtime_ulonglong_put(unsigned long long *dest, const unsigned long long *src,
                     size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else if( (stride != 1) || (nelems == 1)){
    /* sequential execution */
    __xbrtime_put_u8_seq((uint64_t)(src),
                         dest,//__xbrtime_ltor((uint64_t)(dest),pe),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }
  //__xbrtime_asm_fence();
}

// --------------------------------------------------------------- PRINT ARRAY
void print_array(uint64_t *array, size_t length) {
  int i = 0;
  for (i = 0; i < length; i++) { 
    printf("%lu ", array[i]); 
  }
}

// ------------------------------------------------------------- MAIN FUNCTION
int main(int argc, char **argv) {

  int       rtn = 0;
  //uint64_t *ptr = NULL;
  size_t     sz = _ALLOC_SIZE_;

  int         i = 0;
  int       len = 8;

  // ptr           = (uint64_t *)(malloc( sz ));
  // ptr[0]        = (uint64_t)  (1234);
  
  uint64_t *arr_A = NULL;
  uint64_t *arr_B = NULL;
  uint64_t *arr_C = NULL;
  arr_A           = (uint64_t *)(malloc( len * sz ));
  arr_B           = (uint64_t *)(malloc( len * sz )); 
  arr_C           = (uint64_t *)(malloc( len * sz )); 

  int num       = 0; 
  for(i=0; i < len; i++) {
    num        += 2;
    arr_A[i]    = num;
    arr_B[i]    = 0;
    arr_C[i]    = 1;
  }

  printf("A: \n");
  print_array(arr_A, len);
  printf("\n");

  printf("B: \n");
  print_array(arr_B, len);
  printf("\n"); 

  printf("C: \n");
  print_array(arr_C, len);
  printf("\n"); 

  printf("\n");

  printf("TESTING PUT...\n");
  printf("\t put src:B dst:A \n");
  for(i=0; i < len; i++) {
    xbrtime_ulonglong_put((unsigned long long *)(arr_B[i]),
                          (unsigned long long *)(arr_A[i]),
                          1,
                          len,
                          sz );
  }
  // ======================================================  
  
  printf("A: \n");
  print_array(arr_A, len);
  printf("\n");

  printf("B: \n");
  print_array(arr_B, len);
  printf("\n");

  printf("C: \n");
  print_array(arr_C, len);
  printf("\n");

  printf("\n");

  printf("TESTING GET...\n");
  printf("\t get src:C dst:A \n");
  for(i=0; i < len; i++) {
    xbrtime_ulonglong_get((unsigned long long *)(arr_C),
                          (unsigned long long *)(arr_A),
                          1,
                          len,
                          sz );
  }  
  // ======================================================
  
  printf("A: \n");
  print_array(arr_A, len);
  printf("\n");

  printf("B: \n");
  print_array(arr_B, len);
  printf("\n");

  printf("C: \n");
  print_array(arr_C, len);
  printf("\n");

}
/* EOF */
