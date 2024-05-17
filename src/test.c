
#include "decimal.h"
#include <stdio.h>
#include "bcd.h"
void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i){
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
  struct Decimal_t *a = init_decimal();
  struct Decimal_t *b = init_decimal();
  struct Decimal_t *c = init_decimal();
  int a_f = 34;
  int b_f = 78866;
  int c_f;
  from_int_to_decimal(a_f, a);
  from_int_to_decimal(b_f, b);
  set_velue_pow(a, 1);
  set_velue_pow(b, 4);
  set_velue_sign(a, -1);
  add_decimal(a, b, c);
  from_decimal_to_int(c, &c_f);
  printf("res =%d\n", c_f);
struct Decimal_t *t = init_decimal();
  char n[20] = {"123456789"};
  from_string_to_decimal(n, t);

  from_int_to_decimal(128, t);
  from_decimal_to_string(t, n);
  printf("test bcd\n");
  int num = 100;
  set_four_bit(&num, 9, 1);
  printf("%d", num);
}