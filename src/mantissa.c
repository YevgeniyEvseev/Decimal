#include "mantissa.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void add_long_Decimal(const long_Decimal *val_1, const long_Decimal *val_2,
                      long_Decimal *res) {
  int tmp_bit = 0;
  long_Decimal tmp;
  clear_long_Decimal(&tmp);
  for (int i = 0; i < 192; ++i) {
    int arr = i / 32;
    int index_bit = i % 32;
    int index_val_1 = ((1 << index_bit) & val_1->bits[arr]) ? 1 : 0;
    int index_val_2 = ((1 << index_bit) & val_2->bits[arr]) ? 1 : 0;
    int sum_bit = tmp_bit + index_val_1 + index_val_2;
    switch (sum_bit) {
    case 0:
      tmp_bit = 0;
      break;
    case 1:
      tmp_bit = 0;
      tmp.bits[arr] = (1 << index_bit) | tmp.bits[arr];
      break;
    case 2:
      tmp_bit = 1;
      break;
    case 3:
      tmp_bit = 1;
      tmp.bits[arr] = (1 << index_bit) | tmp.bits[arr];
      break;

    default:
      assert("default add_long_Decimal");
      break;
    }
  }
  tmp.sign = val_1->sign;
  tmp.exp_decimal = val_1->exp_decimal;
  *res = copy_long_Decimal(&tmp);
}

void sub_long_Decimal(const long_Decimal *val_1, const long_Decimal *val_2,
                      long_Decimal *res) {
  int tmp_bit = 0;
  long_Decimal invert_val_2, tmp; //, once;
  clear_long_Decimal(&invert_val_2);
  clear_long_Decimal(&tmp);
  // clear_long_Decimal(&once);

  for (int i = 0; i < 6; ++i) {
    invert_val_2.bits[i] = ~(val_2->bits[i]);
  }
  invert_val_2.bits[0] += 1;
  // once.bits[0] = 0;
  // add_long_Decimal(&invert_val_2, &once, &invert_val_2);
  add_long_Decimal(val_1, &invert_val_2, &tmp);
  // add_long_Decimal(res, &once, res);
  clear_long_Decimal(res);
  *res = copy_long_Decimal(&tmp);
}

void clear_long_Decimal(long_Decimal *dst) {
  for (int i = 0; i < 6; ++i) {
    dst->bits[i] = 0;
  }
  dst->sign = 1;
  dst->exp_decimal = 0;
}

long_Decimal copy_long_Decimal(const long_Decimal *val) {
  long_Decimal tmp;
  clear_long_Decimal(&tmp);
  for (int k = 0; k < 6; ++k) {
    tmp.bits[k] = val->bits[k];
  }
  tmp.exp_decimal = val->exp_decimal;
  tmp.sign = val->sign;
  return tmp;
}

int mul_long_Decimal(const long_Decimal *val_1, const long_Decimal *val_2,
                     long_Decimal *res) {
  int offset_count = 0;
  long_Decimal tmp, val_1_copy;
  clear_long_Decimal(&tmp);
  val_1_copy = copy_long_Decimal(val_1);

  for (int i = 0; i < 192; ++i) {
     if (get_decimal_bit(val_2, i)){
      if (offset_mantissa_left(&val_1_copy, offset_count) == FAIL) {
        return FAIL;
      }
      add_long_Decimal(&tmp, &val_1_copy, &tmp);
      offset_count = 1;
    } else {
      offset_count++;
    }
  }
  tmp.sign = val_1_copy.sign * val_2->sign;
  tmp.exp_decimal = val_1->exp_decimal + val_2->exp_decimal;
  *res = copy_long_Decimal(&tmp);
  return OK;
}

int offset_mantissa_left(long_Decimal *val, unsigned count) {
  for (int j = 0; j < count; ++j) {
    if ((val->bits[5] & 0x80000000) != 0)
      return FAIL;
    for (int i = 5; i > 0; i--) {
      val->bits[i] = (val->bits[i] << 1);
      if ((val->bits[i - 1] & 0x80000000) != 0) {
        val->bits[i] = (val->bits[i] | 1);
      }
    }
    val->bits[0] = (val->bits[0] << 1);
  }
  return OK;
}

int pow_mantissa(long_Decimal *val, unsigned n) {
  long_Decimal prod;
  long_Decimal mult;
  clear_long_Decimal(&prod);
  prod.bits[0] = 1;
  mult = copy_long_Decimal(val);
  while (n > 0) {
    if (n % 2 == 1) {
      if (mul_long_Decimal(&prod, &mult, &prod) == FAIL)
        return FAIL;
      n = n - 1;
    } else {
      if (mul_long_Decimal(&mult, &mult, &mult) == FAIL)
        return FAIL;
      n /= 2;
    }
  }
  *val = copy_long_Decimal(&prod);
  return OK;
}

int get_decimal_bit(const long_Decimal *n, int index_bit) {
  int arr = index_bit / 32;
  int i_bit = index_bit % 32;
  return (n->bits[arr] >> index_bit) & 0x1;
}

int cmp_long_decimal(const long_Decimal *val_1, const long_Decimal *val_2) {
  for (int i = 5; i >= 0; i--) {
    if (val_1->bits[i] > val_2->bits[i])
      return 1;
    if (val_1->bits[i] < val_2->bits[i])
      return -1;
  }
  return 0;
}

int div_long_Decimal(const long_Decimal *val_1, const long_Decimal *val_2,
                     long_Decimal *res, long_Decimal *mod) {
  clear_long_Decimal(res);
  clear_long_Decimal(mod);
  for (int i = 191; i >= 0; i--) {
    offset_mantissa_left(res, 1);
    offset_mantissa_left(mod, 1);
    int bit_delit = get_decimal_bit(val_1, i);
    if (bit_delit != 0) {
      mod->bits[0] = mod->bits[0] | 1;
    }
    if (cmp_long_decimal(mod, val_2) >= 0) {
      sub_long_Decimal(mod, val_2, mod);
      res->bits[0] = res->bits[0] | 0x1;
    }
  }
}

int high_order_bit(const long_Decimal *src){
  for (int i = 191; i >= 0; i--) {
    if (get_decimal_bit(src, i)) return i;
  }
  return -1;
}

void round_decimal(long_Decimal *n, const long_Decimal *mod){
  long_Decimal one;
  clear_long_Decimal(&one);
  one.bits[0] = 1;
  if (mod->bits[0] > 0) {
    if (get_decimal_bit(n, 0)) {
      add_long_Decimal(n, &one, n);
    }
  }
}