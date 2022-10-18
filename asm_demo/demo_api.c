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

void __xbrtime_get_u8_seq( uint64_t base_src, uint64_t base_dest, uint32_t pe,
                           uint32_t nelems, uint32_t stride );
void __xbrtime_put_u8_seq( uint64_t base_src, uint64_t base_dest, uint32_t pe,
                           uint32_t nelems, uint32_t stride );


// ------------------------------------------------------------------ ASSEMBLY
/*

__asm__ __volatile__ ( "...;"
                       "...;" 
                      : ... );

  .global __xbrtime_get_u8_seq
  .type __xbrtime_get_u8_seq, @function
__xbrtime_get_u8_seq:
  eaddie e10, a2, 0
  mv x31, zero
.get_u8_seq:
  eld x30, 0(a0)
  add a0, a0, a4
  add x31,x31,1
  sd x30, 0(a1)
  add a1, a1, a4
  bne x31,a3,.get_u8_seq
  ret
  .size __xbrtime_get_u8_seq, .-__xbrtime_get_u8_seq

  #---------------------------------------------------

  .global __xbrtime_put_u8_seq
  .type __xbrtime_put_u8_seq, @function
__xbrtime_put_u8_seq:
  eaddie e11, a2, 0
  mv x31, zero
.put_u8_seq:
  ld x30, 0(a0)
  add a0, a0, a4
  add x31,x31,1
  esd x30, 0(a1)
  add a1,a1,a4
  bne x31,a3,.put_u8_seq
  ret
  .size __xbrtime_put_u8_seq, .-__xbrtime_put_u8_seq

*/

// ----------------------------------------------------------- U8 GET FUNCTION
void xbrtime_ulonglong_get(unsigned long long *dest, const unsigned long long *src,
                     size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else if( (stride != 1) || (nelems == 1)){
    /* sequential execution */
    __xbrtime_get_u8_seq(__xbrtime_ltor((uint64_t)(src),pe),
                         (uint64_t)(dest),
                         xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }else{
    /* aggregate requests */
    __xbrtime_get_u8_agg(__xbrtime_ltor((uint64_t)(src),pe),
                         (uint64_t)(dest),
                         xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }
  __xbrtime_asm_fence();
}

// ----------------------------------------------------------- U8 PUT FUNCTION
void xbrtime_ulonglong_put(unsigned long long *dest, const unsigned long long *src,
                     size_t nelems, int stride, int pe){
  if(nelems == 0){
    return;
  }else if( (stride != 1) || (nelems == 1)){
    /* sequential execution */
    __xbrtime_put_u8_seq((uint64_t)(src),
                         __xbrtime_ltor((uint64_t)(dest),pe),
                         xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }else{
    /* aggregate requests */
    __xbrtime_put_u8_agg((uint64_t)(src),
                         __xbrtime_ltor((uint64_t)(dest),pe),
                         xbrtime_decode_pe(pe),
                         (uint32_t)(nelems),
                         (uint32_t)(stride*sizeof(unsigned long long)));
  }
  __xbrtime_asm_fence();
}


// ------------------------------------------------------------- MAIN FUNCTION
int main(int argc, char **argv) {

  int       rtn = 0;
  uint64_t *ptr = NULL;
  size_t     sz = _ALLOC_SIZE_;

  ptr           = (uint64_t *)(malloc( sz ));
  ptr[0]        = (uint64_t)  (1234);

  xbrtime_ulonglong_get((unsigned long long *)(ptr),
                        (unsigned long long *)(ptr),
                        1,
                        1,
                        1 );  

  xbrtime_ulonglong_put((unsigned long long *)(ptr),
                        (unsigned long long *)(ptr),
                        1,
                        1,
                        1 );

}
/* EOF */
