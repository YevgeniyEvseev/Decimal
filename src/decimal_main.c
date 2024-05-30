// #include "decimal.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bcd.h"
#include "limits.h"
#include "mantissa.h"

typedef struct {
  int bits[4];
} Decimal_t;

enum Oper_m { MUL, DIV, MOD };

void set_value(Decimal_t *s, int val) { s->bits[0] = val; }

Decimal_t *init_decimal() {
  Decimal_t *tmp = malloc(1 * sizeof(Decimal_t));
  for (int i = 0; i < 3; ++i) {
    tmp->bits[i] = 0;
  }
}

void print_decimal(const Decimal_t *val) {
  for (int i = 0; i < 3; ++i) {
    printf("%x\n", val->bits[i]);
  }
}

void set_bit_decimal(Decimal_t *dst, int number_bit) {
  int index_arr = number_bit / 32;
  int num_bit = number_bit % 32;
  dst->bits[index_arr] = (1 << num_bit) | dst->bits[index_arr];
}

int get_value_pow(Decimal_t const *val) {
  return ((val->bits[3] & 0x0000FF00) >> 8);
}

int get_value_sign(Decimal_t const *val) {
  return ((val->bits[3] & 0xA0000000)) ? -1 : 1;
}

void set_value_pow(Decimal_t *des, int val) {
  if (val > 28)
    assert("pow is not correct");
  des->bits[3] = des->bits[3] | (val << 8);
}

int get_value_mantissa(const Decimal_t *val, unsigned index) {
  int res;
  if (index < 3) {
    res = val->bits[index];
  }
  return res;
}

void set_value_sign(Decimal_t *des, int val) {
  if (val > 1)
    assert("sign is not correct");
  if (val == -1)
    des->bits[3] = des->bits[3] | (0x1 << 31);
}

unsigned float_to_unsigned(float d) {
  unsigned res;
  memcpy(&res, &d, sizeof(float));
  return res;
}

int exp_from_float(unsigned d) {
  int res = d >> 23;
  res = res & 0x000000ff;
  return res;
}

int mantisa_from_float(unsigned bit_float) {
  int res = 1;
  int bit_res = 1;
  bit_float = bit_float | (1 << 23);
  for (int i = 22; i > 0; i--, bit_res++) {
    if (bit_float & (1 << i)) {
      res = res | (1 << bit_res);
    }
  }
  return res;
}

void clear_decimal(Decimal_t *dst) {
  for (int i = 0; i < 4; ++i) {
    dst->bits[i] = 0;
  }
}

int decimal_to_mantissa(const Decimal_t *src, long_Decimal *dst) {
  clear_long_Decimal(dst);
  dst->exp_decimal = get_value_pow(src);
  dst->sign = get_value_sign(src);
  for (int i = 0; i < 3; ++i) {
    dst->bits[i] = src->bits[i];
  }
}

int align_exp_mantissa(const Decimal_t *val_1, const Decimal_t *val_2,
                       long_Decimal *new_val_1, long_Decimal *new_val_2) {
  long_Decimal ten;
  clear_long_Decimal(&ten);
  ten.bits[0] = 10;
  decimal_to_mantissa(val_1, new_val_1);
  decimal_to_mantissa(val_2, new_val_2);
  int diff = new_val_1->exp_decimal - new_val_2->exp_decimal;
  pow_mantissa(&ten, abs(diff));

  if (diff < 0) {
    mul_long_Decimal(new_val_1, &ten, new_val_1);
    new_val_1->exp_decimal += abs(diff);
  }
  if (diff > 0) {
    mul_long_Decimal(new_val_2, &ten, new_val_2);
    new_val_2->exp_decimal += abs(diff);
  }
  return OK;
}

int from_decimal_to_float(Decimal_t const *src, float *dst) {
  // printf("test %d\n", src->bits[0]);
  float res = 0;
  double degree = pow(10, get_value_pow(src));
  int sign = get_value_sign(src);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 32; ++j) {
      if ((src->bits[i] >> j) & 0x1)
        res += pow(2, i * 32 + j);
    }
  }

  res /= degree;
  *dst = res * sign;
  return 0;
}

int from_float_to_decimal(float src, Decimal_t *dst) {
  clear_decimal(dst);
  Decimal_t *tmp = init_decimal();
  unsigned bit_float = float_to_unsigned(src);
  int sign = (0xA0000000 & bit_float);
  if (sign != 0)
    set_value_sign(dst, 1);
  int exp_float = exp_from_float(bit_float);
  int mantisa = mantisa_from_float(bit_float);

  if (exp_float == 255)
    return 1;
  if (bit_float == 0) {
    return 0;
  }
  int exp = exp_float - 127;
  if (abs(exp) > 96)
    return 1;
  if (exp > 23) {
    for (int i = 0; i < 23; ++i, exp--) {
      if (mantisa & (1 << i))
        set_bit_decimal(dst, exp);
    }
    return 0;
  }
  dst->bits[0] = mantisa;
  set_bit_decimal(tmp, abs(exp));
  // if (!div_decimal(dst, tmp, dst)) return 1;

  return 0;
}


int from_decimal_to_int(Decimal_t const *src, int *dst) {
  if (src->bits[1] != 0 || src->bits[2] != 0)
    return FAIL;
  if (src->bits[0] < 0)
    return FAIL;
  *dst = src->bits[0];
}

int from_int_to_decimal(int src, Decimal_t *dst) {
  if (src < 0) {
    clear_decimal(dst);
    set_value_sign(dst, -1);
    src = (-1) * src;
  }
  dst->bits[0] = src;
}

int is_digit(char c) { return (c >= '0' && c <= '9') ? 1 : 0; }


int from_long_decimal_decimal(const long_Decimal *src, Decimal_t *dst) {
  int count_bit = high_order_bit(src);
  clear_decimal(dst);

  if (count_bit == -1) return 0;
  int tmp_pow = src->exp_decimal;
  if (tmp_pow > 28)
    return 1;
  long_Decimal copy_src;
  copy_src = copy_long_Decimal(src);
  
  if (count_bit > 95) {
    long_Decimal ten, mod;
    clear_long_Decimal(&ten);
    ten.bits[0] = 10;
    if (count_bit - 95 > src->exp_decimal - 1) {
      return 1;
    }
    while (copy_src.bits[3] != 0) {
      long_Decimal tmp;
      div_long_Decimal(&copy_src, &ten, &tmp, &mod);
      copy_src = copy_long_Decimal(&tmp);
      tmp_pow--;
    }
    round_decimal(&copy_src,&mod);    
  }
  set_value_sign(dst, src->sign);
  set_value_pow(dst, tmp_pow);

  for (int i = 0; i < 3; ++i) {
    dst->bits[i] = copy_src.bits[i];
  }
  return 0;
}

int from_string_to_decimal(const char *src, Decimal_t *dst) {
  char c;
  int count = 0, flag_pow = 0, flag_sign = 0;
  long_Decimal res, ten;
  clear_long_Decimal(&res);
  clear_long_Decimal(&ten);
  ten.bits[0] = 10;
  while ((c = *src++) != '\0') {
    if (flag_pow == 1)
      count++;
    switch (c) {
    case ' ':
      break;
    case '-':
      if (res.sign == -1)
        return 1;
      res.sign = -1;
      break;
    case '.':
      if (flag_pow == 1)
        return 1;
      flag_pow = 1;
      break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '0':
      long_Decimal tmp;
      clear_long_Decimal(&tmp);
      tmp.bits[0] = c - '0';
      mul_long_Decimal(&res, &ten, &res);
      add_long_Decimal(&res, &tmp, &res);
      break;
    default:
      return 1;
    }
  }
  res.exp_decimal = count;
  int res_er = from_long_decimal_decimal(&res, dst);
  if (res_er != 0)
    return 1;
  return 0;
}

void print_int_bit(int n) {
  for (int i = 31; i >= 0; i--) {
    printf("%d", ((0x1 << i) & n) ? 1 : 0);
  }
  printf("\n");
}

int is_null(const Decimal_t *n) {
  for (int i = 0; i < 3; i++) {
    if (n->bits[i] != 0)
      return FAIL;
  }
  return OK;
}



int add_decimal(Decimal_t const *val_1, Decimal_t const *val_2,
                Decimal_t *res) {
  long_Decimal new_val_1, new_val_2, res_mantissa;
  align_exp_mantissa(val_1, val_2, &new_val_1, &new_val_2);
  if (new_val_1.sign == new_val_2.sign) {
    add_long_Decimal(&new_val_1, &new_val_2, &res_mantissa);
  } else {
    if (cmp_long_decimal(&new_val_1, &new_val_2)>=0){
    sub_long_Decimal(&new_val_1, &new_val_2, &res_mantissa);
    } else{
    sub_long_Decimal(&new_val_2, &new_val_1, &res_mantissa);
    }
  }
  int res_err=from_long_decimal_decimal(&res_mantissa, res);
  return res_err;
}

int sub_decimal(Decimal_t const *val_1, Decimal_t const *val_2,
                Decimal_t *res) {
  long_Decimal new_val_1, new_val_2, res_mantissa;
  align_exp_mantissa(val_1, val_2, &new_val_1, &new_val_2);
  if (new_val_1.sign == new_val_2.sign) {
    if (cmp_long_decimal(&new_val_1, &new_val_2)>=0){
    sub_long_Decimal(&new_val_1, &new_val_2, &res_mantissa);
    } else{
      new_val_2.sign *= (-1);
      sub_long_Decimal(&new_val_2, &new_val_1, &res_mantissa);
    }
  } else {
    add_long_Decimal(&new_val_1, &new_val_2, &res_mantissa);
  }
  int res_err=from_long_decimal_decimal(&res_mantissa, res);
  return res_err;
}

int is_long_decimal_null(const long_Decimal *n) {
  for (int i = 0; i < 6; ++i){
    if (n->bits[i] != 0) return FAIL;
  }
  return OK;
}

int oper_mul_div(Decimal_t const *val_1, Decimal_t const *val_2, int oper ,Decimal_t *res){
  long_Decimal new_val_1, new_val_2, res_mantissa, mod;
  int result=align_exp_mantissa(val_1, val_2, &new_val_1, &new_val_2);
  switch (oper)
  {
  case MUL:
    mul_long_Decimal(&new_val_1, &new_val_2, &res_mantissa);
    break;
  
  case DIV:
    long_Decimal ten;
    clear_long_Decimal(&ten);
    ten.bits[0] = 10;
    while (1)
    {  
      div_long_Decimal(&new_val_1, &new_val_2, &res_mantissa, &mod);
      if(is_long_decimal_null(&mod) || res_mantissa.exp_decimal>27){
        if (is_long_decimal_null(&res_mantissa)) return 1;
        break;
      }
      mul_long_Decimal(&new_val_1, &ten, &new_val_1);
      new_val_1.exp_decimal++;
    }
    break;

   case MOD:   
      div_long_Decimal(&new_val_1, &new_val_2, &mod, &res_mantissa);
    break;
  default:
    break;
  }
  return from_long_decimal_decimal(&res_mantissa, res);
}

int mul_decimal(Decimal_t const *val_1, Decimal_t const *val_2,
        Decimal_t *res){
  long_Decimal new_val_1, new_val_2, res_mantissa;
  decimal_to_mantissa(val_1, &new_val_1);
  decimal_to_mantissa(val_2, &new_val_2);

  mul_long_Decimal(&new_val_1, &new_val_2, &res_mantissa);
  return from_long_decimal_decimal(&res_mantissa, res);
}

int div_decimal(const Decimal_t *val_1,
                 const Decimal_t *val_2, Decimal_t *res){
  if (is_null(val_2)) return 2;
  return oper_mul_div(val_1, val_2, DIV, res);
}

int mod_decimal(const Decimal_t *val_1,
                 const Decimal_t *val_2, Decimal_t *res){
  if (is_null(val_2)) return 2;
  return oper_mul_div(val_1, val_2, MOD, res);
}

int ctor_int(Decimal_t *dst, int n) {
  clear_decimal(dst);
  return from_int_to_decimal(n, dst);
}
int ctor_double(Decimal_t *dst, double n) {
  clear_decimal(dst);
  return from_float_to_decimal(n, dst);
}
int ctor_string(Decimal_t *dst, const char *n) {
  clear_decimal(dst);
  return from_string_to_decimal(n, dst);
}
