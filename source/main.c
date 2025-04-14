#include <stdio.h>
#include <stdlib.h>

#include "Decimal.h"
// #include "source/Decimal_def.h"

int main() {
  struct Decimal_t *n1 = init_decimal();
#if 0
  BCD_t res;
  n1.bit[0] = 1502754129;
  n1.bit[1] = 2;
  n1.bit[2] = 2222222233;
  n1.bit[3] = 0;

  int t = 0x80000000;
  print_bit_int(t);
  t = t >> 31;
  print_bit_int(t);
  print_BCD(&res);
  // offset_bit(&res);
  Decimal_to_BCD(&res, &n1);
  print_BCD(&res);
#endif
  char str[35] = {0};
  set_degree_decimal(n1, 10);
  set_sign_decimal(n1, 1);
  print_decimal(n1);

  // decimal_to_str(n1, str);
  printf("decimal degree %d\n", get_degree_decimal(n1));
  printf("decimal sign %d\n", get_sign_decimal(n1));
}