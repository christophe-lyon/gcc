/* PR target/94743 */
/* { dg-do compile } */
/* { dg-skip-if "do not override -mfloat-abi" { *-*-* } { "-mfloat-abi=*" } {"-mfloat-abi=hard" } } */
/* { dg-options "-mfloat-abi=hard" } */

/* Check that we emit a warning when compiling an IRQ handler without
   -mgeneral-regs-only.  */
/* Also check that we save and restore the VFP registers clobbered
   locally.  */
typedef struct {
  double fpdata[32];
} dummy_t;

dummy_t global_d;
dummy_t global_d1;

/* This function may clobber VFP registers, but it is a leaf function:
   we can analyze which registers to save.  */
__attribute__ ((interrupt("IRQ"))) void IRQ_HDLR_Test(void)
{ /* { dg-warning { FP registers might be clobbered despite 'interrupt' attribute: compile with -mgeneral-regs-only} "" { target *-*-* } . } */
  global_d.fpdata[3] += global_d.fpdata[3] * global_d1.fpdata[3];
}
/* { dg-final { scan-assembler-times "vpush.64\t{d\\d+, d\\d+, d\\d+}" 1 } } */
/* { dg-final { scan-assembler-times "vldm\tsp!, {d\\d+-d\\d+}" 1 } } */

/* This function does not need to clobber VFP registers.  */
/* Do we want to emit a (useless?) warning?  */
__attribute__ ((interrupt("IRQ"))) void IRQ_HDLR_Test2(void)
{ /* { dg-warning { FP registers might be clobbered despite 'interrupt' attribute: compile with -mgeneral-regs-only} "" { target *-*-* } . } */
  global_d.fpdata[3] = 1.0;
}
