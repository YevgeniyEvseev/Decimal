//#include "decimal.h"
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "mantissa.h"
#include "limits.h"

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
  if(val==-1) des->bits[3] = des->bits[3] | (1 << 31);
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

int decimal_to_mantissa(const Decimal_t *src, Decimal_mantissa *dst){
  clear_decimal_mantissa(dst);
  dst->exp_decimal = get_value_pow(src);
  dst->sign = get_value_sign(src);
  for (int i = 0; i < 3;++i){
    dst->bits[i] = src->bits[i];
  }
}


int align_exp_mantissa(const Decimal_t *val_1,const Decimal_t *val_2,
              Decimal_mantissa *new_val_1, Decimal_mantissa *new_val_2){
  Decimal_mantissa ten;
  clear_decimal_mantissa(&ten);
  ten.bits[0] = 10;
  decimal_to_mantissa(val_1, new_val_1);
  decimal_to_mantissa(val_2, new_val_2);
  int diff = new_val_1->exp_decimal - new_val_2->exp_decimal;
  if (pow_mantissa(&ten, abs(diff)) == FAIL) return FAIL;
  
  if(diff<0) {
    mul_decimal_mantissa(new_val_1, &ten, new_val_1);
    new_val_1->exp_decimal += abs(diff);
  }
  if(diff>0) {
    mul_decimal_mantissa(new_val_2, &ten, new_val_2);
    new_val_1->exp_decimal += abs(diff);
  }
 
  return OK;
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

int add_decimal( Decimal_t const *val_1,  Decimal_t const *val_2,
         Decimal_t *res) {
  Decimal_mantissa new_val_1, new_val_2, res_mantissa;
   align_exp_mantissa(val_1, val_2, &new_val_1, &new_val_2);
   printf("sign %d\n",new_val_1.sign);
   printf("sign %d\n",new_val_2.sign);
   if (new_val_1.sign == new_val_2.sign) {
     add_decimal_mantissa(&new_val_1, &new_val_2, &res_mantissa);
   } else {
     sub_decimal_mantissa(&new_val_1, &new_val_2, &res_mantissa);
     printf("minus");
   }
   printf("%d\n", res_mantissa.bits[0]);
   // mantissa_to_decimal(&res_mantissa, Decimal_t *dst);
}

int sub_decimal( Decimal_t const *val_1,  Decimal_t const *val_2,
         Decimal_t *res) {
  Decimal_mantissa new_val_1, new_val_2, res_mantissa;
  
  
  new_val_1.bits[0] = 64;
  new_val_2.bits[0] = 9;

  // align_decimal(val_1, val_2, &new_val_1, &new_val_2);
   sub_decimal_mantissa(&new_val_1, &new_val_2, &res_mantissa);
   printf("%d\n", res_mantissa.bits[0]);
   // full_dec_to_decimal(res_mantissa, res);
}


int mantissa_to_decimal(const Decimal_mantissa *src, Decimal_t *dst){}


int from_decimal_to_int(Decimal_t const *src, int *dst){
  if (src->bits[1] != 0 || src->bits[2] != 0) return FAIL;
  if (src->bits[0]<0) return FAIL;
  *dst = src->bits[0];
}

int from_int_to_decimal(int src, Decimal_t *dst){
  if(src<0){
    clear_decimal(dst);
    set_velue_sign(dst, -1);
    src = (-1) * src;
  }
  dst->bits[0] = src;
}