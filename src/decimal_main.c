//#include "decimal.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
  int bits[4];
} Decimal_t;

void set_value(Decimal_t *s, int val) { s->bits[0] = val; }

Decimal_t *init_decimal() {
  Decimal_t *tmp = malloc(1 * sizeof(Decimal_t));
  for (int i = 0; i < 3; ++i) {
    tmp->bits[i] = 0;
  }
}

void print_decimal(const Decimal_t *val) {
  for (int i = 0; i < 3;++i){
    printf("%x\n", val->bits[i]);
  }
}

void set_bit_decimal(Decimal_t *dst, int number_bit){
  int index_arr = number_bit / 32;
  int num_bit = number_bit % 32;
  dst->bits[index_arr] = (1 << num_bit) | dst->bits[index_arr] ;
}

int get_value_pow(Decimal_t const *val) {
  return ((val->bits[3] & 0x0000FF00) >> 8);
}

int get_value_sign(Decimal_t const *val) {
  
  return ((val->bits[3] & 0xA0000000))? -1 : 1;
}

void set_velue_pow(Decimal_t *des, int val) {
  if (val > 28)
    assert("pow is not correct");
  des->bits[3] = des->bits[3] | (val << 8);
}

void set_velue_sign(Decimal_t *des, int val) {
  if (val > 1)
    assert("sign is not correct");
  des->bits[3] = des->bits[3] | (val << 31);
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
  for (int i = 22; i > 0; i--, bit_res++){
    if (bit_float & (1 << i)){
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



int from_decimal_to_float(Decimal_t const *src, float *dst) {
  //printf("test %d\n", src->bits[0]);
  float res = 0;
  double degree = pow(10, get_value_pow(src));
  int sign = get_value_sign(src);
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 32; ++j) {
      if ((src->bits[i] >> j) & 0x1)
        res += pow(2, i*32+j);
    }
  }
  
  res /= degree;
 // printf("res=%f\n", res*sign);
  *dst = res*sign;
  return 0;
}

int from_float_to_decimal(float src, Decimal_t *dst) {
  clear_decimal(dst);
  Decimal_t *tmp = init_decimal();
  unsigned bit_float = float_to_unsigned(src);
  int sign = (0xA0000000 & bit_float);
  if (sign != 0) set_velue_sign(dst, 1);
  int exp_float = exp_from_float(bit_float);
  int mantisa = mantisa_from_float(bit_float);
  
  if (exp_float == 255) return 1;
  if (bit_float == 0) {
    return 0;
  }
  int exp = exp_float - 127;
  if (abs(exp) > 96) return 1;
  if (exp > 23) {
    for (int i = 0; i < 23; ++i, exp--){
      if (mantisa & (1 << i)) set_bit_decimal(dst, exp);
    }
    return 0;
  }
  dst->bits[0] = mantisa;
  set_bit_decimal(tmp, abs(exp));
 // if (!div_decimal(dst, tmp, dst)) return 1;

  return 0;
}

