#
# _DEMO_API_MORELLO_ASM_S_
#

  .file "demo_api_morello_asm.s"
  .text
  .align 1

  #---------------------------------------------------
  # xBGAS ASM API functions are formatted as follows:
  # __xbrtime_{get,put}_OPERAND_{seq,agg}
  #   where,
  #   - {get,put} correponds to receive and send
  #   - OPERAND is one of:
  #     - u1 = unsigned one byte
  #     - u2 = unsigned two byte
  #     - u4 = unsigned four byte
  #     - u8 = unsigned eight byte
  #     - s1 = signed one byte
  #     - s2 = signed two byte
  #     - s4 = signed four byte
  #     - s8 = signed eight byte
  #   - {seq,agg} corresponds to sequential
  #             and aggregated transfers
  #---------------------------------------------------
  # Calling Convention
  #   - X0 = a0 = base src address
  #   - X1 = a1 = base dest address
  #   -    = a2 = remote pe
  #   - X2 = a3 = nelems
  #   - X3 = a4 = stride (in bytes)
  #---------------------------------------------------

  .global __xbrtime_get_u8_seq
  .type __xbrtime_get_u8_seq, @function
__xbrtime_get_u8_seq:
  MOV X12, XZR
.get_u8_seq:
  LDRD X10, [X0]
  ADD X0, X0, X3
  ADD X12, X12, #1
  STRD X10, [X1]
  ADD X1, X1, X3
  CMP X12, X2
  BNE .get_u8_seq
  RET
  .size __xbrtime_get_u8_seq, .-__xbrtime_get_u8_seq

  #---------------------------------------------------

  .global __xbrtime_put_u8_seq
  .type __xbrtime_put_u8_seq, @function
__xbrtime_put_u8_seq:
  MOV X12, XZR
.put_u8_seq:
  LDRD X10, [X0]
  ADD X0, X0, X3
  ADD X12, X12, #1
  STRD X10, [X1]
  ADD X1, X1, X3
  CMP X10, X2
  BNE .put_u8_seq
  RET
  .size __xbrtime_put_u8_seq, .-__xbrtime_put_u8_seq

  #---------------------------------------------------

  .global __xbrtime_asm_fence
  .type __xbrtime_asm_fence, @function
__xbrtime_asm_fence:
  DSB SY
  ISB
  RET
  .size __xbrtime_asm_fence, .-__xbrtime_asm_fence

  #---------------------------------------------------

  .global __xbrtime_asm_quiet_fence
  .type __xbrtime_asm_quiet_fence, @function
__xbrtime_asm_quiet_fence:
  DMB SY
  RET
  .size __xbrtime_asm_quiet_fence, .-__xbrtime_asm_quiet_fence
  
  #-- EOF
