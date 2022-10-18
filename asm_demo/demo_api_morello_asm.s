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
  #   - X2 = a2 = remote pe
  #   - X3 = a3 = nelems
  #   - X4 = a4 = stride (in bytes)
  #---------------------------------------------------

  .global __xbrtime_get_u8_seq
  .type __xbrtime_get_u8_seq, @function
__xbrtime_get_u8_seq:
  MOV X15, XZR
.get_u8_seq:
  LDR X14, [X0]
  ADD X0, X0, X4
  ADD X15, X15, #1
  STR X14, [X1]
  ADD X1, X1, X4
  BNE X15, X3, .get_u8_seq
  RET
  .size __xbrtime_get_u8_seq, .-__xbrtime_get_u8_seq

  #---------------------------------------------------

  .global __xbrtime_put_u8_seq
  .type __xbrtime_put_u8_seq, @function
__xbrtime_put_u8_seq:
  MOV X15, XZR
.put_u8_seq:
  LDR X14, [X0]
  ADD X0, X0, X4
  ADD X15, X15, #1
  STR X14, [X1]
  ADD X1, X1, X4
  BNE x15, X3, .put_u8_seq
  RET
  .size __xbrtime_put_u8_seq, .-__xbrtime_put_u8_seq

  #-- EOF
