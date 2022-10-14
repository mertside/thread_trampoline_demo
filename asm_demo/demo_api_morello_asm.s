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
  #   - a0 = base src address
  #   - a1 = base dest address
  #   - a2 = remote pe
  #   - a3 = nelems
  #   - a4 = stride (in bytes)
  #---------------------------------------------------

  .global __xbrtime_get_u8_seq
  .type __xbrtime_get_u8_seq, @function
__xbrtime_get_u8_seq:
  ADD e10, a2, 0
  MOV x31, zero
.get_u8_seq:
  LDR x30, 0(a0)
  ADD a0, a0, a4
  ADD x31,x31,1
  STR x30, 0(a1)
  ADD a1, a1, a4
  BNE x31,a3,.get_u8_seq
  RET
  .size __xbrtime_get_u8_seq, .-__xbrtime_get_u8_seq

  #---------------------------------------------------

  .global __xbrtime_put_u8_seq
  .type __xbrtime_put_u8_seq, @function
__xbrtime_put_u8_seq:
  ADD e11, a2, 0
  MOV x31, zero
.put_u8_seq:
  LDR x30, 0(a0)
  ADD a0, a0, a4
  ADD x31,x31,1
  STR x30, 0(a1)
  ADD a1,a1,a4
  BNE x31,a3,.put_u8_seq
  RET
  .size __xbrtime_put_u8_seq, .-__xbrtime_put_u8_seq

  #-- EOF
