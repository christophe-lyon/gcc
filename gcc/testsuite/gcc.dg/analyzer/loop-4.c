// FIXME:
/* { dg-additional-options "-fno-analyzer-state-purge" } */

/* Example of nested loops.  */

#include "analyzer-decls.h"

void test(void)
{
  int i, j, k;

  __analyzer_dump_exploded_nodes (0); /* { dg-warning "1 exploded node" } */

  for (i=0; i<256; i++) {

    __analyzer_eval (i >= 0); /* { dg-warning "TRUE" "true" } */
      /* { dg-warning "UNKNOWN" "unknown" { target *-*-* } .-1 } */

    __analyzer_eval (i < 256); /* { dg-warning "TRUE" } */

    for (j=0; j<256; j++) {

      __analyzer_eval (j >= 0); /* { dg-warning "TRUE" "true" } */
      /* { dg-warning "UNKNOWN" "unknown" { target *-*-* } .-1 } */

      __analyzer_eval (j < 256); /* { dg-warning "TRUE" } */

      __analyzer_dump_exploded_nodes (0); /* { dg-warning "3 exploded nodes" } */

      for (k=0; k<256; k++) {

	__analyzer_eval (k >= 0); /* { dg-warning "TRUE" "true" } */
	/* { dg-warning "UNKNOWN" "unknown" { target *-*-* } .-1 } */

	__analyzer_eval (k < 256); /* { dg-warning "TRUE" } */

	__analyzer_dump_exploded_nodes (0); /* { dg-warning "4 exploded nodes" } */
      }
    }
  }

  __analyzer_dump_exploded_nodes (0); /* { dg-warning "1 exploded node" } */
}
