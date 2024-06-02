#include "bcd.h"
#include "decimal.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void decimal_to_bcd(const struct Decimal_t *dst, BCD_t *src) {
  clear_bcd(src);
  for (int i = 95; i >= 0; i--) {
    int index_arr = i / 32;
    int index_bit = i % 32;
    int val_arr = get_value_mantissa(dst, index_arr);
    check_and_correct_decimal(src);
    int val_bit = (val_arr >> index_bit) & 0x1;
    ofset_bcd_left(src);
    src->bits[0] += val_bit;
  }
  src->sign = get_value_sign(dst);
  src->exp = get_value_pow(dst);
}

void ofset_bcd_left(BCD_t *val) {
  for (int i = 3; i > 0; i--) {
    val->bits[i] = val->bits[i] << 1;
    if (val->bits[i - 1] & 0x80000000)
      val->bits[i] += 1;
  }
  val->bits[0] = val->bits[0] << 1;
}

void clear_bcd(BCD_t *n) {
  for (int i = 0; i < 4; ++i) {
    n->bits[i] = 0;
  }
}

void check_and_correct_decimal(BCD_t *n) {
  for (int i = 31; i >= 0; i--) {
    int index_arr = i / 8;
    int index_bit = i % 8;
    int tmp = (n->bits[index_arr] >> (index_bit * 4)) & 0xf;
    if (tmp > 4) {
      tmp += 3;
      // clear need 1/2 bite
      n->bits[index_arr] = (~(0xf << (index_bit * 4))) & n->bits[index_arr];
      // set val tmp
      n->bits[index_arr] = (tmp << (index_bit * 4)) | n->bits[index_arr];
    }
  }
}

void from_decimal_to_string(const struct Decimal_t *src, char *dst) {
  if (is_null(src) == OK) {
    dst[0] = '0';
    return;
  }
  BCD_t tmp;
  char res[35] = {0};
  char str_null[35] = {0};
  int index_res = 0, flag_null = 0, len_str = 0;
  decimal_to_bcd(src, &tmp);
  int exp = tmp.exp;
  if (tmp.sign == -1) {
    str_null[index_res++] = '-';
  }
  for (int i = 31; i >= 0; i--) {
    int arr = i / 8;
    int i_bit = i % 8;
    int c = (tmp.bits[arr] >> i_bit * 4) & 0xf;
    if (c != 0) {
      flag_null = 1;
    }
    //пропускаем не значищушие нули
    if (c == 0 && flag_null == 0)
      continue;
    res[len_str++] = '0' + c;
  }

  if (len_str < (exp)) {
    int count = exp - len_str + index_res;
    for (int i = index_res; i <= count; i++) {
      str_null[i] = '0';
      len_str++;
    }
  }
  strcpy(dst, str_null);
  strcat(dst, res);
  if (exp > 0) {
    char c = '.';
    int sign = (tmp.sign > 0) ? 0 : -1;
    for (int i = len_str - exp - 1 * sign; i <= len_str + 1; ++i) {
      char tmp = dst[i];
      dst[i] = c;
      c = tmp;
    }
  }
}

int bcd_to_int(const BCD_t *src, int *dst) {
  unsigned val = 0, ten = 1;
  int exp = src->exp;

  for (int i = 0; i < 32; ++i) {
    int arr = i / 8;
    int i_bit = i % 8;
    int c = (src->bits[arr] >> i_bit * 4) & 0xf;
    if (exp > 0) {
      exp--;
    } else {
      if (c == 0)
        continue;
      c *= ten;
      ten *= 10;
      val += c;
      if (val > __INT32_MAX__)
        return 1;
    }
  }
  *dst = val;
  return 0;
}