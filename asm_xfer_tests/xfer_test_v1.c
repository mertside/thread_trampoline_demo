 /*
  * _XFER_TEST_V1_C_
  *
  */

//#include "xbrtime.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <inttypes.h>

#define _ALLOC_SIZE_ 8

// ============================================================================

// ------------------------------------------------------- FUNCTION PROTOTYPES
void __xbrtime_asm_fence();
void __xbrtime_asm_quiet_fence();

void __xbrtime_get_u1_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );
void __xbrtime_put_u1_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );

void __xbrtime_get_u2_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );
void __xbrtime_put_u2_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );

void __xbrtime_get_u4_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );
void __xbrtime_put_u4_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );

void __xbrtime_get_u8_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );
void __xbrtime_put_u8_seq( uint64_t base_src, uint64_t base_dest,//uint32_t pe,
                           uint32_t nelems, uint32_t stride );

// ============================================================================

// ------------------------------------------------------------------ ASSEMBLY
/*
__asm__ __volatile__ ( "...;"
                       "...;" 
                      : ... );
  add a1, a1, a4
  bne x31,a3,.get_u8_seq
  ret
*/

// ============================================================================

// ----------------------------------------------------------- U1 GET FUNCTION
void xbrtime_uchar_get(unsigned char *dest, const unsigned char *src,
                       size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_get_u1_seq(src,//__xbrtime_ltor((uint64_t)(src),pe),
                         (uint64_t)(dest),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned char)));
  }
  //__xbrtime_asm_fence();
}

// ----------------------------------------------------------- U1 PUT FUNCTION
void xbrtime_uchar_put(unsigned char *dest, const unsigned char *src,
                       size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_put_u1_seq((uint64_t)(src),
                         dest,//__xbrtime_ltor((uint64_t)(dest),pe),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned char)));
  }
  //__xbrtime_asm_fence();
}

// ============================================================================

// ----------------------------------------------------------- U2 GET FUNCTION
void xbrtime_ushort_get(unsigned short *dest, const unsigned short *src,
                        size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_get_u2_seq(src,//__xbrtime_ltor((uint64_t)(src),pe),
                         (uint64_t)(dest),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned short)));
  }
  //__xbrtime_asm_fence();
}

// ----------------------------------------------------------- U2 PUT FUNCTION
void xbrtime_ushort_put(unsigned short *dest, const unsigned short *src,
                        size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_put_u2_seq((uint64_t)(src),
                         dest,//__xbrtime_ltor((uint64_t)(dest),pe),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned short)));
  }
  //__xbrtime_asm_fence();
}

// ============================================================================

// ----------------------------------------------------------- U4 GET FUNCTION
void xbrtime_ulong_get(unsigned long *dest, const unsigned long *src,
                     size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_get_u4_seq(src,//__xbrtime_ltor((uint64_t)(src),pe),
                         (uint64_t)(dest),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long)));
  }
  //__xbrtime_asm_fence();
}

// ----------------------------------------------------------- U4 PUT FUNCTION
void xbrtime_ulong_put(unsigned long *dest, const unsigned long *src,
                     size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_put_u4_seq((uint64_t)(src),
                         dest,//__xbrtime_ltor((uint64_t)(dest),pe),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long)));
  }
  //__xbrtime_asm_fence();
}

// ============================================================================

// ----------------------------------------------------------- U8 GET FUNCTION
void xbrtime_ulonglong_get(unsigned long long *dest, 
                           const unsigned long long *src, 
                           size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
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
void xbrtime_ulonglong_put(unsigned long long *dest, 
                           const unsigned long long *src,
                           size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else /*if( (stride != 1) || (nelems == 1))*/{
    /* sequential execution */
    __xbrtime_put_u8_seq((uint64_t)(src),
                         dest,//__xbrtime_ltor((uint64_t)(dest),pe),
                         //xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }
  //__xbrtime_asm_fence();
}

// ============================================================================

// ------------------------------------------------------- TEST UNSIGNED 1 BYTE
void test_u1() {
  printf("\ntest_u1\n");
  size_t     sz = 1;
  int       len = 1;
  // ...   ...   ...   ...   ...
  unsigned char *var_X  = NULL;
  unsigned char *var_Y  = NULL;
  unsigned char *var_Z  = NULL;
  var_X            = (unsigned char *)(malloc( sz ));
  var_Y            = (unsigned char *)(malloc( sz ));
  var_Z            = (unsigned char *)(malloc( sz ));
  *var_X           = 255; 
  *var_Y           = 0;
  *var_Z           = 1;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  printf("\n");
  printf("var_X: %u \n", *var_X);
  printf("var_Y: %u \n", *var_Y);
  printf("var_Z: %u \n", *var_Z);
  // ======================================================
  printf("TESTING PUT...\n");
  printf("\t put dst:Y src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_uchar_put((unsigned char *)(var_Y),
                    (unsigned char *)(var_X),
                    len,
                    1,
                    1 );
  // ======================================================
  printf("var_X: %u \n", *var_X);
  printf("var_Y: %u \n", *var_Y);
  printf("var_Z: %u \n", *var_Z);
  // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:Z src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_uchar_get((unsigned char *)(var_Z),
                    (unsigned char *)(var_X),
                    len,
                    1,
                    1 ); 
  // ======================================================
  printf("var_X: %u \n", *var_X);
  printf("var_Y: %u \n", *var_Y);
  printf("var_Z: %u \n", *var_Z);
}

// ------------------------------------------------------- TEST UNSIGNED 2 BYTE
void test_u2() {
  printf("\ntest_u2\n");
  size_t     sz = 2;
  int       len = 1;
  // ...   ...   ...   ...   ...
  unsigned short *var_X  = NULL;
  unsigned short *var_Y  = NULL;
  unsigned short *var_Z  = NULL;
  var_X            = (unsigned short *)(malloc( sz ));
  var_Y            = (unsigned short *)(malloc( sz ));
  var_Z            = (unsigned short *)(malloc( sz ));
  *var_X           = 65535; 
  *var_Y           = 0;
  *var_Z           = 1;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  printf("\n");
  printf("var_X: %hu \n", *var_X);
  printf("var_Y: %hu \n", *var_Y);
  printf("var_Z: %hu \n", *var_Z);
  // ======================================================
  printf("TESTING PUT...\n");
  printf("\t put dst:Y src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_ushort_put((unsigned short *)(var_Y),
                     (unsigned short *)(var_X),
                     len,
                     1,
                     1 );
  // ======================================================
  printf("var_X: %hu \n", *var_X);
  printf("var_Y: %hu \n", *var_Y);
  printf("var_Z: %hu \n", *var_Z);
  // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:Z src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_ushort_get((unsigned short *)(var_Z),
                     (unsigned short *)(var_X),
                     len,
                     1,
                     1 ); 
  // ======================================================
  printf("var_X: %hu \n", *var_X);
  printf("var_Y: %hu \n", *var_Y);
  printf("var_Z: %hu \n", *var_Z);
}

// ------------------------------------------------------- TEST UNSIGNED 4 BYTE
void test_u4() {
  printf("\ntest_u4\n");
  size_t     sz = 4;
  int       len = 1;
  // ...   ...   ...   ...   ...
  unsigned long *var_X  = NULL;
  unsigned long *var_Y  = NULL;
  unsigned long *var_Z  = NULL;
  var_X            = (unsigned long *)(malloc( sz ));
  var_Y            = (unsigned long *)(malloc( sz ));
  var_Z            = (unsigned long *)(malloc( sz ));
  *var_X           = 4294967295; 
  *var_Y           = 0;
  *var_Z           = 1;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  printf("\n");
  printf("var_X: %lu \n", *var_X);
  printf("var_Y: %lu \n", *var_Y);
  printf("var_Z: %lu \n", *var_Z);
  // ======================================================
  printf("TESTING PUT...\n");
  printf("\t put dst:Y src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_ulong_put((unsigned long *)(var_Y),
                    (unsigned long *)(var_X),
                    len,
                    1,
                    1 );
  // ======================================================
  printf("var_X: %lu \n", *var_X);
  printf("var_Y: %lu \n", *var_Y);
  printf("var_Z: %lu \n", *var_Z);
  // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:Z src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_ulong_get((unsigned long *)(var_Z),
                    (unsigned long *)(var_X),
                    len,
                    1,
                    1 ); 
  // ======================================================
  printf("var_X: %lu \n", *var_X);
  printf("var_Y: %lu \n", *var_Y);
  printf("var_Z: %lu \n", *var_Z);
}

// ------------------------------------------------------- TEST UNSIGNED 8 BYTE
void test_u8() {
  printf("\ntest_u8\n");
  size_t     sz = 8;
  int       len = 1;
  // ...   ...   ...   ...   ...
  uint64_t *var_X  = NULL;
  uint64_t *var_Y  = NULL;
  uint64_t *var_Z  = NULL;
  var_X            = (uint64_t *)(malloc( sz ));
  var_Y            = (uint64_t *)(malloc( sz ));
  var_Z            = (uint64_t *)(malloc( sz ));
  *var_X           = 18446744073709551615; // 9223372036854775807;
  *var_Y           = 0;
  *var_Z           = 1;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  printf("\n");
  printf("var_X: %llu \n", *var_X);
  printf("var_Y: %llu \n", *var_Y);
  printf("var_Z: %llu \n", *var_Z);
  // ======================================================
  printf("TESTING PUT...\n");
  printf("\t put dst:Y src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_ulonglong_put((unsigned long long *)(var_Y),
                        (unsigned long long *)(var_X),
                        len,
                        1,
                        1 );
  // ======================================================
  printf("var_X: %llu \n", *var_X);
  printf("var_Y: %llu \n", *var_Y);
  printf("var_Z: %llu \n", *var_Z);
  // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:Z src:X \n"); // dst, src, nelem, stride, pe
  xbrtime_ulonglong_get((unsigned long long *)(var_Z),
                        (unsigned long long *)(var_X),
                        len,
                        1,
                        1 ); 
  // ======================================================
  printf("var_X: %llu \n", *var_X);
  printf("var_Y: %llu \n", *var_Y);
  printf("var_Z: %llu \n", *var_Z);
}

// ============================================================================

// ------------------------------------------------------------- PRINT ARRAY U1
void print_array_u1(uint8_t *array, size_t length) {
  int i = 0;
  for (i = 0; i < length; i++) { 
    printf("%u ", array[i]); 
  }
  printf("\n");
}

// ============================================================================

// ------------------------------------------------------------- PRINT ARRAY U2
void print_array_u2(uint16_t *array, size_t length) {
  int i = 0;
  for (i = 0; i < length; i++) { 
    printf("%hu ", array[i]); 
  }
  printf("\n");
}

// ============================================================================

// ------------------------------------------------------------- PRINT ARRAY U4
void print_array_u4(uint32_t *array, size_t length) {
  int i = 0;
  for (i = 0; i < length; i++) { 
    printf("%lu ", array[i]); 
  }
  printf("\n");
}

// ============================================================================

// ------------------------------------------------------------- PRINT ARRAY U8
void print_array_u8(uint64_t *array, size_t length) {
  int i = 0;
  for (i = 0; i < length; i++) { 
    printf("%llu ", array[i]); 
  }
  printf("\n");
}

// ============================================================================

// ------------------------------------------------- TEST ARRAY UNSIGNED 1 BYTE
void test_array_u1() {
  printf("\ntest_array_u1\n");
  size_t     sz = 1;
  int       len = 8;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  uint8_t *arr_A = NULL;
  uint8_t *arr_B = NULL;
  uint8_t *arr_C = NULL;
  arr_A           = (uint8_t *)(malloc( len * sz ));
  arr_B           = (uint8_t *)(malloc( len * sz )); 
  arr_C           = (uint8_t *)(malloc( len * sz )); 
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  int num       = 0; 
  for(int i=0; i < len; i++) {
    num        += 2;
    arr_A[i]    = num;
    arr_B[i]    = 0;
    arr_C[i]    = 1;
  }
 // ======================================================
  printf("A: \n");
  print_array_u1(arr_A, len);
  printf("B: \n");
  print_array_u1(arr_B, len);
  printf("C: \n");
  print_array_u1(arr_C, len);
  // ======================================================
  printf("\nTESTING PUT...\n");
  printf("\t put dst:B src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_uchar_put((unsigned long *)(arr_B),
                    (unsigned long *)(arr_A),
                    len,
                    1,
                    1 ); 
  // ======================================================    
  printf("A: \n");
  print_array_u1(arr_A, len);
  printf("B: \n");
  print_array_u1(arr_B, len);
  printf("C: \n");
  print_array_u1(arr_C, len);
 // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:C src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_uchar_get((unsigned long *)(arr_C),
                    (unsigned long *)(arr_A),
                    len,
                    1,
                    1 ); 
  // ======================================================
  printf("A: \n");
  print_array_u1(arr_A, len);
  printf("B: \n");
  print_array_u1(arr_B, len);
  printf("C: \n");
  print_array_u1(arr_C, len);
}

// ============================================================================

// ------------------------------------------------- TEST ARRAY UNSIGNED 2 BYTE
void test_array_u2() {
  printf("\ntest_array_u2\n");
  size_t     sz = 2;
  int       len = 8;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  uint16_t *arr_A = NULL;
  uint16_t *arr_B = NULL;
  uint16_t *arr_C = NULL;
  arr_A           = (uint16_t *)(malloc( len * sz ));
  arr_B           = (uint16_t *)(malloc( len * sz )); 
  arr_C           = (uint16_t *)(malloc( len * sz )); 
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  int num       = 0; 
  for(int i=0; i < len; i++) {
    num        += 2;
    arr_A[i]    = num;
    arr_B[i]    = 0;
    arr_C[i]    = 1;
  }
 // ======================================================
  printf("A: \n");
  print_array_u2(arr_A, len);
  printf("B: \n");
  print_array_u2(arr_B, len);
  printf("C: \n");
  print_array_u2(arr_C, len);
  // ======================================================
  printf("\nTESTING PUT...\n");
  printf("\t put dst:B src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_ushort_put((unsigned short *)(arr_B),
                     (unsigned short *)(arr_A),
                     len,
                     1,
                     1 ); 
  // ======================================================    
  printf("A: \n");
  print_array_u2(arr_A, len);
  printf("B: \n");
  print_array_u2(arr_B, len);
  printf("C: \n");
  print_array_u2(arr_C, len);
 // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:C src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_ushort_get((unsigned short *)(arr_C),
                     (unsigned short *)(arr_A),
                     len,
                     1,
                     1 ); 
  // ======================================================
  printf("A: \n");
  print_array_u2(arr_A, len);
  printf("B: \n");
  print_array_u2(arr_B, len);
  printf("C: \n");
  print_array_u2(arr_C, len);
}

// ============================================================================

// ------------------------------------------------- TEST ARRAY UNSIGNED 4 BYTE
void test_array_u4() {
  printf("\ntest_array_u4\n");
  // size_t     sz = 4;
  int       len = 8;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  unsigned long *arr_A = malloc( len * sizeof(unsigned long) );
  unsigned long *arr_B = malloc( len * sizeof(unsigned long) );
  unsigned long *arr_C = malloc( len * sizeof(unsigned long) );
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  int num       = 0; 
  for(int i=0; i < len; i++) {
    num        += 2;
    arr_A[i]    = num;
    arr_B[i]    = 0;
    arr_C[i]    = 1;
  }
 // ======================================================
  printf("A: \n");
  print_array_u4(arr_A, len);
  printf("B: \n");
  print_array_u4(arr_B, len);
  printf("C: \n");
  print_array_u4(arr_C, len);
  // ======================================================
  printf("\nTESTING PUT...\n");
  printf("\t put dst:B src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_ulong_put((unsigned long *)(arr_B),
                    (unsigned long *)(arr_A),
                    len,
                    1,
                    1 ); 
  // ======================================================    
  printf("A: \n");
  print_array_u4(arr_A, len);
  printf("B: \n");
  print_array_u4(arr_B, len);
  printf("C: \n");
  print_array_u4(arr_C, len);
 // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:C src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_ulong_get((unsigned long *)(arr_C),
                    (unsigned long *)(arr_A),
                    len,
                    1,
                    1 ); 
  // ======================================================
  printf("A: \n");
  print_array_u4(arr_A, len);
  printf("B: \n");
  print_array_u4(arr_B, len);
  printf("C: \n");
  print_array_u4(arr_C, len);
}

// ============================================================================

// ------------------------------------------------- TEST ARRAY UNSIGNED 8 BYTE
void test_array_u8() {
  printf("\ntest_array_u8\n");
  // size_t     sz = _ALLOC_SIZE_;
  int       len = 8;
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  uint64_t *arr_A = malloc( len * sizeof(uint64_t) );
  uint64_t *arr_B = malloc( len * sizeof(uint64_t) );
  uint64_t *arr_C = malloc( len * sizeof(uint64_t) );
  // ...   ...   ...   ...   ...   ...   ...   ...   ...   ...
  int num       = 0; 
  for(int i=0; i < len; i++) {
    num        += 2;
    arr_A[i]    = num;
    arr_B[i]    = 0;
    arr_C[i]    = 1;
  }
 // ======================================================
  printf("A: \n");
  print_array_u8(arr_A, len);
  printf("B: \n");
  print_array_u8(arr_B, len);
  printf("C: \n");
  print_array_u8(arr_C, len);
  // ======================================================
  printf("\nTESTING PUT...\n");
  printf("\t put dst:B src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_ulonglong_put((unsigned long long *)(arr_B),
                        (unsigned long long *)(arr_A),
                        len,
                        1,
                        1 ); 
  // ======================================================    
  printf("A: \n");
  print_array_u8(arr_A, len);
  printf("B: \n");
  print_array_u8(arr_B, len);
  printf("C: \n");
  print_array_u8(arr_C, len);
 // ======================================================
  printf("\nTESTING GET...\n");
  printf("\t get dst:C src:A \n"); // dst, src, nelem, stride, pe
  xbrtime_ulonglong_get((unsigned long long *)(arr_C),
                        (unsigned long long *)(arr_A),
                        len,
                        1,
                        1 ); 
  // ======================================================
  printf("A: \n");
  print_array_u8(arr_A, len);
  printf("B: \n");
  print_array_u8(arr_B, len);
  printf("C: \n");
  print_array_u8(arr_C, len);
}

// ============================================================================

// ------------------------------------------------------------- MAIN FUNCTION
int main(int argc, char **argv) {
  // int       rtn = 0;
  // //uint64_t *ptr = NULL;
  // size_t     sz = _ALLOC_SIZE_;
  // int         i = 0;
  // int       len = 8;
  // // ptr           = (uint64_t *)(malloc( sz ));
  // // ptr[0]        = (uint64_t)  (1234);

  int modeSelection = 0;

  if(argc > 1) {
    modeSelection = atoi(argv[1]);
  }

  if(modeSelection == 1) {
    test_u1();
  } else if(modeSelection == 2) {
    test_u2();
  } else if(modeSelection == 4) {
    test_u4();
  } else if(modeSelection == 8) {
    test_u8();
  } else if(modeSelection == 11) {
    test_array_u1();
  } else if(modeSelection == 12) {
    test_array_u2();
  } else if(modeSelection == 14) {
    test_array_u4();
  } else if(modeSelection == 18) {
    test_array_u8();
  } else {
    printf("\nEnter one of the following arguments\n");
    printf("  1: test_u1()\n");
    printf("  2: test_u2()\n");
    printf("  4: test_u4()\n");
    printf("  8: test_u8()\n");
    printf(" 11: test_array_u1()\n");
    printf(" 12: test_array_u2()\n");
    printf(" 14: test_array_u4()\n");
    printf(" 18: test_array_u8()\n");
  }


}
/* EOF */
