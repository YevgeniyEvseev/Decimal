#include "string.h"
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
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  int res1 = ctor_string(d1, "123.23");
  int res2 = ctor_string(d2, "123.23");

 int r= is_less(d1, d2);
}