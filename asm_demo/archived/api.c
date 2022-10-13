/*
 * _API_C_
 *
 */

#include "xbrtime.h"
#include <inttypes.h>

// ------------------------------------------------------- FUNCTION PROTOTYPES 
void __xbrtime_asm_fence();
void __xbrtime_asm_quiet_fence();

void __xbrtime_get_u4_seq( uint64_t base_src, uint64_t base_dest, uint32_t pe,
                           uint32_t nelems, uint32_t stride );
void __xbrtime_put_u4_seq( uint64_t base_src, uint64_t base_dest, uint32_t pe,
                           uint32_t nelems, uint32_t stride );

// ------------------------------------------------------------- MAIN FUNCTION
int main(int argc, char **argv) {

}

/* EOF */
