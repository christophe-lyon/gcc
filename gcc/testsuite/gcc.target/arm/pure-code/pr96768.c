/* { dg-do compile } */
/* { dg-options "-mpure-code" } */

int f2 (int x, int y)
{
  switch (x)
    {
    case 0: return y + 0;
    case 1: return y + 1;
    case 2: return y + 2;
    case 3: return y + 3;
    case 4: return y + 4;
    case 5: return y + 5;
    }
  return y;
}

/* We do not want any load from literal pool, but accept loads from r7
   (frame pointer, used at -O0).  */
/* { dg-final { scan-assembler-not "ldr\tr\\d+, \\\[r\[0-689\]+\\\]" } } */
/* { dg-final { scan-assembler "text,\"0x20000006\"" } } */
