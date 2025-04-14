#include <stdio.h>
#include <stdlib.h>

#include "Decimal_def.h"
// #include "Decimal.h"

int get_sign_decimal(Decimal_t *value) { return value->bit[3] > 0 ? 0 : -1; }

int get_degree_decimal(Decimal_t *value) {
  unsigned tmp = (value->bit[3] >> 16) & 0xFF;
  if (tmp > 28) ERROR("cannot value degree", CRITICAL);
  return tmp;
}

void set_sign_decimal(Decimal_t *value, int sign) {
  unsigned tmp = 1;
  if (value->bit[3] < 0 && sign < 0) return;
  if (sign < 0) tmp = tmp << 31;
  value->bit[3] = value->bit[3] | tmp;
}
void set_degree_decimal(Decimal_t *value, int degree) {
  int sign = get_sign_decimal(value);
  value->bit[3] = 0;
  if (degree < 0 || degree > 28) {
    ERROR("value degree is not correct", WARNING);
    return;
  }
  degree = degree << 16;
  value->bit[3] = value->bit[3] | degree;
  set_sign_decimal(value, sign);
}

Decimal_t *init_decimal() {
  Decimal_t *tmp = malloc(sizeof(Decimal_t *));
  empty_bit((Decimal_t *)tmp);
  return tmp;
}

void decimal_to_str(Decimal_t *value, char *str) {
  BCD_t val_bcd;
  char tmp[32];
  int degree = get_degree_decimal(value);
  BCD_to_Decimal(value, &val_bcd);
  if (get_sign_decimal(value) == -1) *str++ = '-';
  for (int i = 0; i < 32; ++i) {
    tmp[i] = '0' + get_nibble(&val_bcd, i);
  }
  int j = 31;
  while (j >= 0 || tmp[j] == '0') {
    j++;
  }
  for (; j >= 0; j--) {
    *str++ = tmp[j];
    // if()
  }
}
