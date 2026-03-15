#include <stdio.h>

#include "bcd.h"
#include "decimal.h"
#include "mantissa.h"
#include "string.h"

void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i) {
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
  char n1[35] = "15";
  char n2[35] = "-233345";
  char n_res[35] = "-10";
  char n[35] = {0};
  struct Decimal_t* d1 = init_decimal();
  struct Decimal_t* d2 = init_decimal();
  struct Decimal_t* res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);

  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string add 2=%s\n", n);

  destroy_decimal(d1);
  destroy_decimal(d2);
  destroy_decimal(res_d);
}