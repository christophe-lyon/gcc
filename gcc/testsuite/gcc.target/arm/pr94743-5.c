/* PR target/94743 */
/* { dg-do compile } */
/* { dg-skip-if "do not override -mfloat-abi" { *-*-* } { "-mfloat-abi=*" } {"-mfloat-abi=hard" } } */
/* Require Neon so that we push d16-d31.  */
/* { dg-require-effective-target arm_neon_ok } */
/* { dg-add-options arm_neon } */
/* { dg-additional-options "-mfloat-abi=hard" } */

/* Check that we emit a warning when compiling an IRQ handler without
   -mgeneral-regs-only.  */
/* Also check that we save and restore the call-clobbered VFP registers.  */
typedef struct {
  double fpdata[32];
} dummy_t;

dummy_t global_d;
dummy_t global_d1;

/* This function may clobber VFP registers.  */
__attribute__ ((interrupt("IRQ"))) void IRQ_HDLR_Test(void)
{ /* { dg-warning { FP registers might be clobbered despite 'interrupt' attribute: compile with -mgeneral-regs-only} "" { target *-*-* } . } */
  /* Force implicit call to memcpy.  */
  global_d = global_d1;
  global_d.fpdata[3] += global_d.fpdata[3] * global_d1.fpdata[3];
}
/* { dg-final { scan-assembler-times "vpush.64\t{d0, d1, d2, d3, d4, d5, d6, d7}" 1 } } */
/* { dg-final { scan-assembler-times "vpush.64\t{d16, d17, d18, d19, d20, d21, d22, d23, d24, d25, d26, d27, d28, d29, d30, d31}" 1 } } */
/* { dg-final { scan-assembler-times "vldm\tsp!, {d16-d31}" 1 } } */
/* { dg-final { scan-assembler-times "vldm\tsp!, {d0-d7}" 1 } } */

/* This function does not need to clobber VFP registers.  */
__attribute__ ((interrupt("IRQ"))) void IRQ_HDLR_Test2(void)
{ /* { dg-warning { FP registers might be clobbered despite 'interrupt' attribute: compile with -mgeneral-regs-only} "" { target *-*-* } . } */
  global_d.fpdata[3] = 1.0;
}
