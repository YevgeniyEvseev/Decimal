
#include "decimal.h"
#include <stdio.h>

void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i){
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
  struct Decimal_t *d = init_decimal();
  struct Decimal_t *t = init_decimal();
  struct Decimal_t *r = init_decimal();
  float dv = -50000000000, dr=0;
  from_float_to_decimal(dv, d);

  from_decimal_to_float(d, &dr);
  printf("%f\n", dr);
  printf("%f\n", dv);
  //print_decimal(d);
  add_decimal(d, t, r);
}