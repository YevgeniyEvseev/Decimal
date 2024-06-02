#include "bcd.h"
#include "decimal.h"
#include "string.h"
#include <stdio.h>
void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i) {
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
  int n;
  struct Decimal_t *d1 = init_decimal();
  int res1 = ctor_string(d1, "123.23");
  from_decimal_to_int(d1, &n);
  destroy_decimal(d1);
}