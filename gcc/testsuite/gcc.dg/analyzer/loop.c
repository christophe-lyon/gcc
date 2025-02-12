/* { dg-additional-options "-fno-analyzer-state-purge" } */

#include "analyzer-decls.h"

void test(void)
{
  int i;

  __analyzer_dump_exploded_nodes (0); /* { dg-warning "1 exploded node" } */

  for (i=0; i<256; i++) {
      __analyzer_eval (i < 256); /* { dg-warning "TRUE" } */
      /* (should report TRUE twice). */

      __analyzer_eval (i == 0); /* { dg-warning "TRUE" "1st" } */
      /* { dg-warning "FALSE" "2nd" { xfail *-*-* } .-1 } */
      /* { dg-warning "UNKNOWN" "status quo" { target *-*-* } .-2 } */
      /* TODO(xfail^^^): ideally we ought to figure out i > 0 after 1st iteration.  */

      __analyzer_eval (i >= 0); /* { dg-warning "TRUE" "1st" } */
      /* { dg-warning "TRUE" "2nd" { xfail *-*-* } } */
      /* { dg-warning "UNKNOWN" "status quo" { target *-*-* } .-2 } */
      /* TODO(xfail^^^): ideally we ought to figure out i >= 0 for all iterations.  */

      __analyzer_dump_exploded_nodes (0); /* { dg-warning "2 exploded nodes" } */
  }

  __analyzer_eval (i >= 256); /* { dg-warning "TRUE" } */

  __analyzer_eval (i == 256); /* { dg-warning "TRUE" "desired" { xfail *-*-* } } */
  /* { dg-warning "UNKNOWN" "status quo" { target *-*-* } .-1 } */
  /* TODO(xfail^^^): it only figures out i >= 256, rather than i == 256.  */

  __analyzer_dump_exploded_nodes (0); /* { dg-warning "1 exploded node" } */
}
