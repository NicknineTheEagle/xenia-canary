/*
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#include <xenia/cpu/libjit/libjit_emit.h>


using namespace xe::cpu;
using namespace xe::cpu::ppc;


namespace xe {
namespace cpu {
namespace libjit {


// Integer arithmetic (A-3)

// XEEMITTER(addx,         0x7C000214, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RD <- (RA) + (RB)

//   if (i.XO.OE) {
//     // With XER update.
//     // This is a different codepath as we need to use llvm.sadd.with.overflow.

//     Function* sadd_with_overflow = Intrinsic::getDeclaration(
//         e.gen_module(), Intrinsic::sadd_with_overflow, jit_type_nint);
//     jit_value_t v = b.CreateCall2(sadd_with_overflow,
//                              e.gpr_value(i.XO.RA), e.gpr_value(i.XO.RB));
//     jit_value_t v0 = b.CreateExtractValue(v, 0);
//     e.update_gpr_value(i.XO.RT, v0);
//     e.update_xer_with_overflow(b.CreateExtractValue(v, 1));

//     if (i.XO.Rc) {
//       // With cr0 update.
//       e.update_cr_with_cond(0, v0, e.get_int64(0), true);
//     }

//     return 0;
//   } else {
//     // No OE bit setting.
//     jit_value_t v = b.CreateAdd(e.gpr_value(i.XO.RA), e.gpr_value(i.XO.RB));
//     e.update_gpr_value(i.XO.RT, v);

//     if (i.XO.Rc) {
//       // With cr0 update.
//       e.update_cr_with_cond(0, v, e.get_int64(0), true);
//     }

//     return 0;
//   }
//   return 0;
// }

XEEMITTER(addcx,        0x7C000014, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(addex,        0x7C000114, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(addi,         0x38000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // if RA = 0 then
  //   RT <- EXTS(SI)
  // else
  //   RT <- (RA) + EXTS(SI)

  jit_value_t v = e.get_int64(XEEXTS16(i.D.DS));
  if (i.D.RA) {
    v = jit_insn_add(f, e.gpr_value(i.D.RA), v);
  }
  e.update_gpr_value(i.D.RT, v);

  return 0;
}

// XEEMITTER(addic,        0x30000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RT <- (RA) + EXTS(SI)

//   Function* sadd_with_overflow = Intrinsic::getDeclaration(
//       e.gen_module(), Intrinsic::sadd_with_overflow, jit_type_nint);
//   jit_value_t v = b.CreateCall2(sadd_with_overflow,
//                            e.gpr_value(i.D.RA), e.get_int64(XEEXTS16(i.D.DS)));
//   e.update_gpr_value(i.D.RT, b.CreateExtractValue(v, 0));
//   e.update_xer_with_carry(b.CreateExtractValue(v, 1));

//   return 0;
// }

XEEMITTER(addicx,       0x34000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(addis,        0x3C000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // if RA = 0 then
  //   RT <- EXTS(SI) || i16.0
  // else
  //   RT <- (RA) + EXTS(SI) || i16.0

  jit_value_t v = e.get_int64(XEEXTS16(i.D.DS) << 16);
  if (i.D.RA) {
    v = jit_insn_add(f, e.gpr_value(i.D.RA), v);
  }
  e.update_gpr_value(i.D.RT, v);

  return 0;
}

XEEMITTER(addmex,       0x7C0001D4, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

// XEEMITTER(addzex,       0x7C000194, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RT <- (RA) + CA

//   Function* sadd_with_overflow = Intrinsic::getDeclaration(
//       e.gen_module(), Intrinsic::sadd_with_overflow, jit_type_nint);
//   jit_value_t ca = jit_insn_and(f, jit_insn_ushr(f, e.xer_value(), 29), 0x1);
//   jit_value_t v = b.CreateCall2(sadd_with_overflow,
//                            e.gpr_value(i.XO.RA), ca);
//   jit_value_t add_value = b.CreateExtractValue(v, 0);
//   e.update_gpr_value(i.XO.RT, add_value);
//   if (i.XO.OE) {
//     // With XER[SO] update too.
//     e.update_xer_with_overflow_and_carry(b.CreateExtractValue(v, 1));
//   } else {
//     // Just CA update.
//     e.update_xer_with_carry(b.CreateExtractValue(v, 1));
//   }

//   if (i.XO.Rc) {
//     // With cr0 update.
//     e.update_cr_with_cond(0, add_value, e.get_int64(0), true);
//   }

//   return 0;
// }

XEEMITTER(divdx,        0x7C0003D2, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(divdux,       0x7C000392, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

// XEEMITTER(divwx,        0x7C0003D6, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // dividend[0:31] <- (RA)[32:63]
//   // divisor[0:31] <- (RB)[32:63]
//   // if divisor = 0 then
//   //   if OE = 1 then
//   //     XER[OV] <- 1
//   //   return
//   // RT[32:63] <- dividend ÷ divisor
//   // RT[0:31] <- undefined

//   jit_value_t dividend = e.trunc_to_int(e.gpr_value(i.XO.RA));
//   jit_value_t divisor = e.trunc_to_int(e.gpr_value(i.XO.RB));

//   // Note that we skip the zero handling block and just avoid the divide if
//   // we are OE=0.
//   BasicBlock* zero_bb = i.XO.OE ?
//       BasicBlock::Create(*e.context(), "", e.fn()) : NULL;
//   BasicBlock* nonzero_bb = BasicBlock::Create(*e.context(), "", e.fn());
//   BasicBlock* after_bb = BasicBlock::Create(*e.context(), "", e.fn());
//   b.CreateCondBr(b.CreateICmpEQ(divisor, b.get_int32(0)),
//                  i.XO.OE ? zero_bb : after_bb, nonzero_bb);

//   if (zero_bb) {
//     // Divisor was zero - do XER update.
//     b.SetInsertPoint(zero_bb);
//     e.update_xer_with_overflow(b.getInt1(1));
//     b.CreateBr(after_bb);
//   }

//   // Divide.
//   b.SetInsertPoint(nonzero_bb);
//   jit_value_t v = b.CreateSDiv(dividend, divisor);
//   v = e.sign_extend(v, jit_type_nint);
//   e.update_gpr_value(i.XO.RT, v);

//   // If we are OE=1 we need to clear the overflow bit.
//   if (i.XO.OE) {
//     e.update_xer_with_overflow(b.getInt1(0));
//   }

//   if (i.XO.Rc) {
//     // With cr0 update.
//     e.update_cr_with_cond(0, v, e.get_int64(0), true);
//   }

//   b.CreateBr(after_bb);

//   // Resume.
//   b.SetInsertPoint(after_bb);

//   return 0;
// }

// XEEMITTER(divwux,       0x7C000396, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // dividend[0:31] <- (RA)[32:63]
//   // divisor[0:31] <- (RB)[32:63]
//   // if divisor = 0 then
//   //   if OE = 1 then
//   //     XER[OV] <- 1
//   //   return
//   // RT[32:63] <- dividend ÷ divisor
//   // RT[0:31] <- undefined

//   jit_value_t dividend = e.trunc_to_int(e.gpr_value(i.XO.RA));
//   jit_value_t divisor = e.trunc_to_int(e.gpr_value(i.XO.RB));

//   // Note that we skip the zero handling block and just avoid the divide if
//   // we are OE=0.
//   BasicBlock* zero_bb = i.XO.OE ?
//       BasicBlock::Create(*e.context(), "", e.fn()) : NULL;
//   BasicBlock* nonzero_bb = BasicBlock::Create(*e.context(), "", e.fn());
//   BasicBlock* after_bb = BasicBlock::Create(*e.context(), "", e.fn());
//   b.CreateCondBr(b.CreateICmpEQ(divisor, b.get_int32(0)),
//                  i.XO.OE ? zero_bb : after_bb, nonzero_bb);

//   if (zero_bb) {
//     // Divisor was zero - do XER update.
//     b.SetInsertPoint(zero_bb);
//     e.update_xer_with_overflow(b.getInt1(1));
//     b.CreateBr(after_bb);
//   }

//   // Divide.
//   b.SetInsertPoint(nonzero_bb);
//   jit_value_t v = b.CreateUDiv(dividend, divisor);
//   v = e.zero_extend(v, jit_type_nint);
//   e.update_gpr_value(i.XO.RT, v);

//   // If we are OE=1 we need to clear the overflow bit.
//   if (i.XO.OE) {
//     e.update_xer_with_overflow(b.getInt1(0));
//   }

//   if (i.XO.Rc) {
//     // With cr0 update.
//     e.update_cr_with_cond(0, v, e.get_int64(0), true);
//   }

//   b.CreateBr(after_bb);

//   // Resume.
//   b.SetInsertPoint(after_bb);

//   return 0;
// }

XEEMITTER(mulhdx,       0x7C000092, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(mulhdux,      0x7C000012, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(mulhwx,       0x7C000096, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(mulhwux,      0x7C000016, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(mulldx,       0x7C0001D2, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(mulli,        0x1C000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // prod[0:127] <- (RA) × EXTS(SI)
  // RT <- prod[64:127]

  // TODO(benvanik): ensure this has the right behavior when the value
  // overflows. It should be truncating the result, but I'm not sure what LLVM
  // does.

  jit_value_t v = jit_insn_mul(f, e.gpr_value(i.D.RA),
                               e.get_int64(XEEXTS16(i.D.DS)));
  e.update_gpr_value(i.D.RT, v);

  return 0;
}

XEEMITTER(mullwx,       0x7C0001D6, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RT <- (RA)[32:63] × (RB)[32:63]

  if (i.XO.OE) {
    // With XER update.
    XEINSTRNOTIMPLEMENTED();
    return 1;
  }

  jit_value_t v = jit_insn_mul(
      f, e.sign_extend(e.gpr_value(i.XO.RA), jit_type_nint),
      e.sign_extend(e.gpr_value(i.XO.RB), jit_type_nint));
  e.update_gpr_value(i.XO.RT, v);

  if (i.XO.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

// XEEMITTER(negx,         0x7C0000D0, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RT <- ¬(RA) + 1

//   if (i.XO.OE) {
//     // With XER update.
//     // This is a different codepath as we need to use llvm.ssub.with.overflow.

//     // if RA == 0x8000000000000000 then no-op and set OV=1
//     // This may just magically do that...

//     Function* ssub_with_overflow = Intrinsic::getDeclaration(
//         e.gen_module(), Intrinsic::ssub_with_overflow, jit_type_nint);
//     jit_value_t v = b.CreateCall2(ssub_with_overflow,
//                              e.get_int64(0), e.gpr_value(i.XO.RA));
//     jit_value_t v0 = b.CreateExtractValue(v, 0);
//     e.update_gpr_value(i.XO.RT, v0);
//     e.update_xer_with_overflow(b.CreateExtractValue(v, 1));

//     if (i.XO.Rc) {
//       // With cr0 update.
//       e.update_cr_with_cond(0, v0, e.get_int64(0), true);
//     }

//     return 0;
//   } else {
//     // No OE bit setting.
//     jit_value_t v = b.CreateSub(e.get_int64(0), e.gpr_value(i.XO.RA));
//     e.update_gpr_value(i.XO.RT, v);

//     if (i.XO.Rc) {
//       // With cr0 update.
//       e.update_cr_with_cond(0, v, e.get_int64(0), true);
//     }

//     return 0;
//   }
// }

// XEEMITTER(subfx,        0x7C000050, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RT <- ¬(RA) + (RB) + 1

//   if (i.XO.OE) {
//     // With XER update.
//     // This is a different codepath as we need to use llvm.ssub.with.overflow.

//     Function* ssub_with_overflow = Intrinsic::getDeclaration(
//         e.gen_module(), Intrinsic::ssub_with_overflow, jit_type_nint);
//     jit_value_t v = b.CreateCall2(ssub_with_overflow,
//                              e.gpr_value(i.XO.RB), e.gpr_value(i.XO.RA));
//     jit_value_t v0 = b.CreateExtractValue(v, 0);
//     e.update_gpr_value(i.XO.RT, v0);
//     e.update_xer_with_overflow(b.CreateExtractValue(v, 1));

//     if (i.XO.Rc) {
//       // With cr0 update.
//       e.update_cr_with_cond(0, v0, e.get_int64(0), true);
//     }

//     return 0;
//   } else {
//     // No OE bit setting.
//     jit_value_t v = b.CreateSub(e.gpr_value(i.XO.RB), e.gpr_value(i.XO.RA));
//     e.update_gpr_value(i.XO.RT, v);

//     if (i.XO.Rc) {
//       // With cr0 update.
//       e.update_cr_with_cond(0, v, e.get_int64(0), true);
//     }

//     return 0;
//   }
// }

XEEMITTER(subfcx,       0x7C000010, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

// XEEMITTER(subficx,      0x20000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RT <- ¬(RA) + EXTS(SI) + 1

//   Function* ssub_with_overflow = Intrinsic::getDeclaration(
//       e.gen_module(), Intrinsic::ssub_with_overflow, jit_type_nint);
//   jit_value_t v = b.CreateCall2(ssub_with_overflow,
//                            e.get_int64(XEEXTS16(i.D.DS)), e.gpr_value(i.D.RA));
//   e.update_gpr_value(i.D.RT, b.CreateExtractValue(v, 0));
//   e.update_xer_with_carry(b.CreateExtractValue(v, 1));

//   return 0;
// }

// XEEMITTER(subfex,       0x7C000110, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // RT <- ¬(RA) + (RB) + CA

//   // TODO(benvanik): possible that the add of rb+ca needs to also check for
//   //     overflow!

//   jit_value_t ca = jit_insn_and(f, jit_insn_ushr(f, e.xer_value(), 29), 0x1);
//   Function* uadd_with_overflow = Intrinsic::getDeclaration(
//       e.gen_module(), Intrinsic::uadd_with_overflow, jit_type_nint);
//   jit_value_t v = b.CreateCall2(uadd_with_overflow,
//                            b.CreateNeg(e.gpr_value(i.XO.RA)),
//                            b.CreateAdd(e.gpr_value(i.XO.RB), ca));
//   jit_value_t v0 = b.CreateExtractValue(v, 0);
//   e.update_gpr_value(i.XO.RT, v0);

//   if (i.XO.OE) {
//     // With XER update.
//     e.update_xer_with_overflow_and_carry(b.CreateExtractValue(v, 1));
//   } else {
//     e.update_xer_with_carry(b.CreateExtractValue(v, 1));
//   }

//   if (i.XO.Rc) {
//     // With cr0 update.
//     e.update_cr_with_cond(0, v0, e.get_int64(0), true);
//   }

//   return 0;
// }

XEEMITTER(subfmex,      0x7C0001D0, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(subfzex,      0x7C000190, XO )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}


// Integer compare (A-4)

XEEMITTER(cmp,          0x7C000000, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // if L = 0 then
  //   a <- EXTS((RA)[32:63])
  //   b <- EXTS((RB)[32:63])
  // else
  //   a <- (RA)
  //   b <- (RB)
  // if a < b then
  //   c <- 0b100
  // else if a > b then
  //   c <- 0b010
  // else
  //   c <- 0b001
  // CR[4×BF+32:4×BF+35] <- c || XER[SO]

  uint32_t BF = i.X.RT >> 2;
  uint32_t L = i.X.RT & 1;

  jit_value_t lhs = e.gpr_value(i.X.RA);
  jit_value_t rhs = e.gpr_value(i.X.RB);
  if (!L) {
    // 32-bit - truncate and sign extend.
    lhs = e.trunc_to_int(lhs);
    lhs = e.sign_extend(lhs, jit_type_nint);
    rhs = e.trunc_to_int(rhs);
    rhs = e.sign_extend(rhs, jit_type_nint);
  }

  e.update_cr_with_cond(BF, lhs, rhs, true);

  return 0;
}

XEEMITTER(cmpi,         0x2C000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // if L = 0 then
  //   a <- EXTS((RA)[32:63])
  // else
  //   a <- (RA)
  // if a < EXTS(SI) then
  //   c <- 0b100
  // else if a > EXTS(SI) then
  //   c <- 0b010
  // else
  //   c <- 0b001
  // CR[4×BF+32:4×BF+35] <- c || XER[SO]

  uint32_t BF = i.D.RT >> 2;
  uint32_t L = i.D.RT & 1;

  jit_value_t lhs = e.gpr_value(i.D.RA);
  if (!L) {
    // 32-bit - truncate and sign extend.
    lhs = e.trunc_to_int(lhs);
    lhs = e.sign_extend(lhs, jit_type_nint);
  }

  jit_value_t rhs = e.get_int64(XEEXTS16(i.D.DS));
  e.update_cr_with_cond(BF, lhs, rhs, true);

  return 0;
}

XEEMITTER(cmpl,         0x7C000040, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // if L = 0 then
  //   a <- i32.0 || (RA)[32:63]
  //   b <- i32.0 || (RB)[32:63]
  // else
  //   a <- (RA)
  //   b <- (RB)
  // if a <u b then
  //   c <- 0b100
  // else if a >u b then
  //   c <- 0b010
  // else
  //   c <- 0b001
  // CR[4×BF+32:4×BF+35] <- c || XER[SO]

  uint32_t BF = i.X.RT >> 2;
  uint32_t L = i.X.RT & 1;

  jit_value_t lhs = e.gpr_value(i.X.RA);
  jit_value_t rhs = e.gpr_value(i.X.RB);
  if (!L) {
    // 32-bit - truncate and zero extend.
    lhs = e.trunc_to_int(lhs);
    lhs = e.zero_extend(lhs, jit_type_nint);
    rhs = e.trunc_to_int(rhs);
    rhs = e.zero_extend(rhs, jit_type_nint);
  }

  e.update_cr_with_cond(BF, lhs, rhs, false);

  return 0;
}

XEEMITTER(cmpli,        0x28000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // if L = 0 then
  //   a <- i32.0 || (RA)[32:63]
  // else
  //   a <- (RA)
  // if a <u i48.0 || SI then
  //   c <- 0b100
  // else if a >u i48.0 || SI then
  //   c <- 0b010
  // else
  //   c <- 0b001
  // CR[4×BF+32:4×BF+35] <- c || XER[SO]

  uint32_t BF = i.D.RT >> 2;
  uint32_t L = i.D.RT & 1;

  jit_value_t lhs = e.gpr_value(i.D.RA);
  if (!L) {
    // 32-bit - truncate and zero extend.
    lhs = e.trunc_to_int(lhs);
    lhs = e.zero_extend(lhs, jit_type_nint);
  }

  jit_value_t rhs = e.get_int64(i.D.DS);
  e.update_cr_with_cond(BF, lhs, rhs, false);

  return 0;
}


// Integer logical (A-5)

XEEMITTER(andx,         0x7C000038, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) & (RB)

  jit_value_t v = jit_insn_and(f, e.gpr_value(i.X.RT), e.gpr_value(i.X.RB));
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(andcx,        0x7C000078, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) & ¬(RB)

  jit_value_t v = jit_insn_xor(f, e.gpr_value(i.X.RB),
                                  e.get_int64(-1));
  v = jit_insn_and(f, e.gpr_value(i.X.RT), v);
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(andix,        0x70000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) & (i48.0 || UI)

  jit_value_t v = jit_insn_and(f, e.gpr_value(i.D.RT), e.get_uint64(i.D.DS));
  e.update_gpr_value(i.D.RA, v);

  // With cr0 update.
  e.update_cr_with_cond(0, v, e.get_int64(0), true);

  return 0;
}

XEEMITTER(andisx,       0x74000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) & (i32.0 || UI || i16.0)

  jit_value_t v = jit_insn_and(f, e.gpr_value(i.D.RT),
                                  e.get_uint64(((uint64_t)i.D.DS) << 16));
  e.update_gpr_value(i.D.RA, v);

  // With cr0 update.
  e.update_cr_with_cond(0, v, e.get_int64(0), true);

  return 1;
}

XEEMITTER(cntlzdx,      0x7C000074, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

// XEEMITTER(cntlzwx,      0x7C000034, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
//   // n <- 32
//   // do while n < 64
//   //   if (RS) = 1 then leave n
//   //   n <- n + 1
//   // RA <- n - 32

//   jit_value_t v = e.gpr_value(i.X.RT);
//   v = e.trunc_to_int(v);

//   std::vector<Type*> arg_types;
//   arg_types.push_back(b.getInt32Ty());
//   Function* ctlz = Intrinsic::getDeclaration(
//       e.fn()->getParent(), Intrinsic::ctlz, arg_types);
//   jit_value_t count = b.CreateCall2(ctlz, v, b.getInt1(1));

//   count = e.zero_extend(count, jit_type_nint);
//   e.update_gpr_value(i.X.RA, count);

//   if (i.X.Rc) {
//     // With cr0 update.
//     e.update_cr_with_cond(0, count, e.get_int64(0), true);
//   }

//   return 0;
// }

XEEMITTER(eqvx,         0x7C000238, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(extsbx,       0x7C000774, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // s <- (RS)[56]
  // RA[56:63] <- (RS)[56:63]
  // RA[0:55] <- i56.s

  jit_value_t v = e.gpr_value(i.X.RT);
  v = e.trunc_to_ubyte(v);
  v = e.sign_extend(v, jit_type_nint);
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // Update cr0.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(extshx,       0x7C000734, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(extswx,       0x7C0007B4, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(nandx,        0x7C0003B8, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(norx,         0x7C0000F8, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- ¬((RS) | (RB))

  jit_value_t v = jit_insn_or(f, e.gpr_value(i.X.RT), e.gpr_value(i.X.RB));
  v = jit_insn_xor(f, v, e.get_int64(-1));
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(orx,          0x7C000378, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) | (RB)

  jit_value_t v = jit_insn_or(f, e.gpr_value(i.X.RT), e.gpr_value(i.X.RB));
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(orcx,         0x7C000338, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(ori,          0x60000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) | (i48.0 || UI)

  jit_value_t v = jit_insn_or(f, e.gpr_value(i.D.RT),
                                 e.get_uint64((uint64_t)i.D.DS));
  e.update_gpr_value(i.D.RA, v);

  return 0;
}

XEEMITTER(oris,         0x64000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) | (i32.0 || UI || i16.0)

  jit_value_t v = jit_insn_or(f, e.gpr_value(i.D.RT),
                                 e.get_uint64(((uint64_t)i.D.DS) << 16));
  e.update_gpr_value(i.D.RA, v);

  return 0;
}

XEEMITTER(xorx,         0x7C000278, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) XOR (RB)

  jit_value_t v = jit_insn_xor(f, e.gpr_value(i.X.RT), e.gpr_value(i.X.RB));
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(xori,         0x68000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) XOR (i48.0 || UI)

  jit_value_t v = jit_insn_xor(f, e.gpr_value(i.D.RT),
                                  e.get_uint64((uint64_t)i.D.DS));
  e.update_gpr_value(i.D.RA, v);

  return 0;
}

XEEMITTER(xoris,        0x6C000000, D  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // RA <- (RS) XOR (i32.0 || UI || i16.0)

  jit_value_t v = jit_insn_xor(f, e.gpr_value(i.D.RT),
                                  e.get_uint64(((uint64_t)i.D.DS) << 16));
  e.update_gpr_value(i.D.RA, v);

  return 0;
}


// Integer rotate (A-6)

XEEMITTER(rldclx,       0x78000010, MDS)(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(rldcrx,       0x78000012, MDS)(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(rldicx,       0x78000008, MD )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(rldiclx,      0x78000000, MD )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // n <- sh[5] || sh[0:4]
  // r <- ROTL64((RS), n)
  // b <- mb[5] || mb[0:4]
  // m <- MASK(b, 63)
  // RA <- r & m

  // uint32_t sh = (i.MD.SH5 << 5) | i.MD.SH;
  // uint32_t mb = (i.MD.MB5 << 5) | i.MD.MB;

  // jit_value_t v = e.gpr_value(i.MD.RS);
  // if (sh) {
  //   v = // rotate by sh
  // }
  // if (mb) {
  //   v = // mask b mb->63
  // }
  // e.update_gpr_value(i.MD.RA, v);

  // if (i.MD.Rc) {
  //   // With cr0 update.
  //   e.update_cr_with_cond(0, v, e.get_int64(0), true);
  // }

  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(rldicrx,      0x78000004, MD )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(rldimix,      0x7800000C, MD )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(rlwimix,      0x50000000, M  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // n <- SH
  // r <- ROTL32((RS)[32:63], n)
  // m <- MASK(MB+32, ME+32)
  // RA <- r&m | (RA)&¬m

  // ROTL32(x, y) = rotl(i64.(x||x), y)
  jit_value_t v = jit_insn_and(f, e.gpr_value(i.M.RT),
                                  e.get_uint64(UINT32_MAX));
  v = jit_insn_or(f, jit_insn_shl(f, v, e.get_uint32(32)), v);
  // (v << shift) | (v >> (32 - shift));
  v = jit_insn_or(f, jit_insn_shl(f, v, e.get_uint32(i.M.SH)),
                     jit_insn_ushr(f, v, e.get_uint32(32 - i.M.SH)));
  uint64_t m = XEMASK(i.M.MB + 32, i.M.ME + 32);
  v = jit_insn_and(f, v, e.get_uint64(m));
  v = jit_insn_or(f, v, jit_insn_and(f, e.gpr_value(i.M.RA),
                                        e.get_uint64(~m)));
  e.update_gpr_value(i.M.RA, v);

  if (i.M.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(rlwinmx,      0x54000000, M  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // n <- SH
  // r <- ROTL32((RS)[32:63], n)
  // m <- MASK(MB+32, ME+32)
  // RA <- r & m

  // The compiler will generate a bunch of these for the special case of SH=0.
  // Which seems to just select some bits and set cr0 for use with a branch.
  // We can detect this and do less work.
  if (!i.M.SH) {
    jit_value_t v = jit_insn_and(f,
        e.trunc_to_int(e.gpr_value(i.M.RT)),
        e.get_uint32((uint32_t)XEMASK(i.M.MB + 32, i.M.ME + 32)));
    v = e.zero_extend(v, jit_type_nint);
    e.update_gpr_value(i.M.RA, v);
    if (i.M.Rc) {
      // With cr0 update.
      e.update_cr_with_cond(0, v, e.get_int64(0), true);
    }
    return 0;
  }

  // ROTL32(x, y) = rotl(i64.(x||x), y)
  jit_value_t v = jit_insn_and(f, e.gpr_value(i.M.RT), e.get_uint64(UINT32_MAX));
  v = jit_insn_or(f, jit_insn_shl(f, v, e.get_uint32(32)), v);
  // (v << shift) | (v >> (32 - shift));
  v = jit_insn_or(f, jit_insn_shl(f, v, e.get_uint32(i.M.SH)),
                     jit_insn_ushr(f, v, e.get_uint32(32 - i.M.SH)));
  v = jit_insn_and(f, v, e.get_uint64(XEMASK(i.M.MB + 32, i.M.ME + 32)));
  e.update_gpr_value(i.M.RA, v);

  if (i.M.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(rlwnmx,       0x5C000000, M  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}


// Integer shift (A-7)

XEEMITTER(sldx,         0x7C000036, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(slwx,         0x7C000030, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // n <- (RB)[59:63]
  // r <- ROTL32((RS)[32:63], n)
  // if (RB)[58] = 0 then
  //   m <- MASK(32, 63-n)
  // else
  //   m <- i64.0
  // RA <- r & m

  jit_value_t v = jit_insn_shl(f, e.gpr_value(i.X.RT), e.gpr_value(i.X.RB));
  v = jit_insn_and(f, v, e.get_uint64(UINT32_MAX));
  e.update_gpr_value(i.X.RA, v);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(sradx,        0x7C000634, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(sradix,       0x7C000674, XS )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(srawx,        0x7C000630, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(srawix,       0x7C000670, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  // n <- SH
  // r <- ROTL32((RS)[32:63], 64-n)
  // m <- MASK(n+32, 63)
  // s <- (RS)[32]
  // RA <- r&m | (i64.s)&¬m
  // CA <- s & ((r&¬m)[32:63]≠0)

  jit_value_t rs64 = e.gpr_value(i.X.RT);
  jit_value_t rs32 = e.trunc_to_int(rs64);

  jit_value_t v;
  jit_value_t ca;
  if (!i.X.RB) {
    // No shift, just a fancy sign extend and CA clearer.
    v = rs32;
    ca = e.get_int64(0);
  } else {
    v = jit_insn_sshr(f, rs32, e.get_uint32(i.X.RB));

    // CA is set to 1 if the low-order 32 bits of (RS) contain a negative number
    // and any 1-bits are shifted out of position 63; otherwise CA is set to 0.
    ca = jit_insn_and(f, jit_insn_lt(f, v, e.get_int32(0)),
                         jit_insn_lt(f, rs64, e.get_int64(0)));
  }
  v = e.sign_extend(v, jit_type_nint);
  e.update_gpr_value(i.X.RA, v);
  e.update_xer_with_carry(ca);

  if (i.X.Rc) {
    // With cr0 update.
    e.update_cr_with_cond(0, v, e.get_int64(0), true);
  }

  return 0;
}

XEEMITTER(srdx,         0x7C000436, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}

XEEMITTER(srwx,         0x7C000430, X  )(LibjitEmitter& e, jit_function_t f, InstrData& i) {
  XEINSTRNOTIMPLEMENTED();
  return 1;
}


void LibjitRegisterEmitCategoryALU() {
  //XEREGISTERINSTR(addx,         0x7C000214);
  XEREGISTERINSTR(addcx,        0X7C000014);
  XEREGISTERINSTR(addex,        0x7C000114);
  XEREGISTERINSTR(addi,         0x38000000);
  //XEREGISTERINSTR(addic,        0x30000000);
  XEREGISTERINSTR(addicx,       0x34000000);
  XEREGISTERINSTR(addis,        0x3C000000);
  XEREGISTERINSTR(addmex,       0x7C0001D4);
  //XEREGISTERINSTR(addzex,       0x7C000194);
  XEREGISTERINSTR(divdx,        0x7C0003D2);
  XEREGISTERINSTR(divdux,       0x7C000392);
  //XEREGISTERINSTR(divwx,        0x7C0003D6);
  //XEREGISTERINSTR(divwux,       0x7C000396);
  XEREGISTERINSTR(mulhdx,       0x7C000092);
  XEREGISTERINSTR(mulhdux,      0x7C000012);
  XEREGISTERINSTR(mulhwx,       0x7C000096);
  XEREGISTERINSTR(mulhwux,      0x7C000016);
  XEREGISTERINSTR(mulldx,       0x7C0001D2);
  XEREGISTERINSTR(mulli,        0x1C000000);
  XEREGISTERINSTR(mullwx,       0x7C0001D6);
  //XEREGISTERINSTR(negx,         0x7C0000D0);
  //XEREGISTERINSTR(subfx,        0x7C000050);
  XEREGISTERINSTR(subfcx,       0x7C000010);
  //XEREGISTERINSTR(subficx,      0x20000000);
  //XEREGISTERINSTR(subfex,       0x7C000110);
  XEREGISTERINSTR(subfmex,      0x7C0001D0);
  XEREGISTERINSTR(subfzex,      0x7C000190);
  XEREGISTERINSTR(cmp,          0x7C000000);
  XEREGISTERINSTR(cmpi,         0x2C000000);
  XEREGISTERINSTR(cmpl,         0x7C000040);
  XEREGISTERINSTR(cmpli,        0x28000000);
  XEREGISTERINSTR(andx,         0x7C000038);
  XEREGISTERINSTR(andcx,        0x7C000078);
  XEREGISTERINSTR(andix,        0x70000000);
  XEREGISTERINSTR(andisx,       0x74000000);
  XEREGISTERINSTR(cntlzdx,      0x7C000074);
  //XEREGISTERINSTR(cntlzwx,      0x7C000034);
  XEREGISTERINSTR(eqvx,         0x7C000238);
  XEREGISTERINSTR(extsbx,       0x7C000774);
  XEREGISTERINSTR(extshx,       0x7C000734);
  XEREGISTERINSTR(extswx,       0x7C0007B4);
  XEREGISTERINSTR(nandx,        0x7C0003B8);
  XEREGISTERINSTR(norx,         0x7C0000F8);
  XEREGISTERINSTR(orx,          0x7C000378);
  XEREGISTERINSTR(orcx,         0x7C000338);
  XEREGISTERINSTR(ori,          0x60000000);
  XEREGISTERINSTR(oris,         0x64000000);
  XEREGISTERINSTR(xorx,         0x7C000278);
  XEREGISTERINSTR(xori,         0x68000000);
  XEREGISTERINSTR(xoris,        0x6C000000);
  XEREGISTERINSTR(rldclx,       0x78000010);
  XEREGISTERINSTR(rldcrx,       0x78000012);
  XEREGISTERINSTR(rldicx,       0x78000008);
  XEREGISTERINSTR(rldiclx,      0x78000000);
  XEREGISTERINSTR(rldicrx,      0x78000004);
  XEREGISTERINSTR(rldimix,      0x7800000C);
  XEREGISTERINSTR(rlwimix,      0x50000000);
  XEREGISTERINSTR(rlwinmx,      0x54000000);
  XEREGISTERINSTR(rlwnmx,       0x5C000000);
  XEREGISTERINSTR(sldx,         0x7C000036);
  XEREGISTERINSTR(slwx,         0x7C000030);
  XEREGISTERINSTR(sradx,        0x7C000634);
  XEREGISTERINSTR(sradix,       0x7C000674);
  XEREGISTERINSTR(srawx,        0x7C000630);
  XEREGISTERINSTR(srawix,       0x7C000670);
  XEREGISTERINSTR(srdx,         0x7C000436);
  XEREGISTERINSTR(srwx,         0x7C000430);
}


}  // namespace libjit
}  // namespace cpu
}  // namespace xe
