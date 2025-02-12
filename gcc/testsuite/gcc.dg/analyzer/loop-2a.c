/* { dg-additional-options "-fno-analyzer-state-purge" } */
#include "analyzer-decls.h"

union u
{
  int i;
};

void test(void)
{
  union u u;

  __analyzer_dump_exploded_nodes (0); /* { dg-warning "1 exploded node" } */


  for (u.i=0; u.i<256; u.i++) {
    __analyzer_eval (u.i < 256); /* { dg-warning "TRUE" "1st" } */
    /* { dg-warning "TRUE" "2nd" { xfail *-*-* } .-1 } */
    /* { dg-bogus "UNKNOWN" "status quo" { xfail *-*-* } .-2 } */
    /* (should report TRUE twice). */

    __analyzer_dump_exploded_nodes (0); /* { dg-warning "2 exploded nodes" } */

    //__analyzer_eval (u.i == 0); /* { d-todo-g-warning "UNKNOWN" "" { xfail *-*-* } } */
      /* { d-todo-g-warning "TRUE" "" { target *-*-* } .-1 } */
      /* TODO(xfail^^^): we're only capturing the first iteration, so
	 we erroneously get i == 0.  */

      //__analyzer_eval (u.i >= 0); /* { d-todo-g-warning "TRUE" } */
  }

  __analyzer_eval (u.i >= 256); /* { dg-warning "TRUE" "desired" { xfail *-*-* } } */
  /* { dg-warning "UNKNOWN" "status quo" { target *-*-* } .-1 } */

  __analyzer_eval (u.i == 256); /* { dg-warning "TRUE" "desired" { xfail *-*-* } } */
  /* { dg-warning "UNKNOWN" "status quo" { target *-*-* } .-1 } */
  /* TODO(xfail^^^): ideally it should figure out i == 256 at exit.  */

  __analyzer_dump_exploded_nodes (0); /* { dg-warning "1 exploded node" } */
}
