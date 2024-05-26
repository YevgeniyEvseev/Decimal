
#include "bcd.h"
#include "decimal.h"
#include <stdio.h>
void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i) {
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
char n_res[35] = "0.000091";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"0.00009");
  int res2 = ctor_string(d2,"0.000001");
  add_decimal(d1, d2, res_d);
   from_decimal_to_string(res_d, n);
}