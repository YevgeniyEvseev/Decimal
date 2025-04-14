#include <stdio.h>

#include "Decimal_def.h"

void empty_bit(void *n) {
  int *tmp = (int *)n;
  for (int i = 0; i < 4; ++i) {
    tmp[i] = 0;
  }
}

int get_decimal_bit(Decimal_t *value, int n) {
  return ((value->bit[n / 32]) >> (n % 32)) & 0x1;
}

void Decimal_to_BCD(BCD_t *dest, Decimal_t *src) {
  int size_empty_bit = 0, count = 0;
  bool_t empty_b = FALSE;

  empty_bit((BCD_t *)dest);

  for (int i = SIZE_DECIMAL - 1; i >= 0; --i) {
    int bit = get_decimal_bit(src, i);
    if (empty_b == FALSE && !bit) {
      continue;
    }
    empty_b = TRUE;
    count++;
    for (int k = 0; k < 128 / SIZE_NIBBLE; k++) {
      if (get_nibble(dest, k) > 4) {
        correrct_nibble(dest, k);
      }
    }
    offset_bit(dest);
    dest->bit[0] = dest->bit[0] | bit;
  }
}

void BCD_to_Decimal(Decimal_t *dest, BCD_t *src) {}

int get_nibble(BCD_t *value, int n) {
  int mask = 0xf;
  return value->bit[n * 4 / 32] >> ((n * 4) % 32) & mask;
}

void correrct_nibble(BCD_t *value, int n) {
  unsigned mask = 0x3 << (n * 4) % 32;
  int i = n * 4 / 32;
  value->bit[i] = value->bit[i] + mask;
}

void offset_bit(BCD_t *value) {
  for (int i = 3; i > 0; i--) {
    unsigned tmp = value->bit[i];
    value->bit[i] = tmp << 1;
    if ((value->bit[i - 1] >> 31)) {
      value->bit[i] = value->bit[i] | 0x1;
    }
  }
  value->bit[0] = (unsigned)value->bit[0] << 1;
}

void print_bit_int(int n) {
  for (int i = sizeof(int) * 8 - 1; i >= 0; --i) {
    int mask = 1 << i;
    printf("%d", !(n & mask) ? 0 : 1);
  }
  printf("\n");
}

void print_decimal(Decimal_t *value) {
  printf("Decimal value ");
  for (int i = 0; i < 4; ++i) {
    print_bit_int(value->bit[i]);
  }
}

void print_BCD(BCD_t *value) {
  printf("BCD value ");
  for (int i = 0; i < 4; ++i) {
    print_bit_int(value->bit[i]);
  }
}
