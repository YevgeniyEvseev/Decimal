#include "mantissa.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


void add_long_Decimal(const long_Decimal *val_1,const long_Decimal *val_2, long_Decimal *res){
  int tmp_bit = 0;
  long_Decimal tmp;
  clear_long_Decimal(&tmp);
  for (int i = 0; i < 192; ++i) {
    int arr = i / 32;
    int index_bit = i % 32;
    int index_val_1 = ((1 << index_bit) & val_1->bits[arr])?1:0;
    int index_val_2 = ((1 << index_bit) & val_2->bits[arr])?1:0;
    int sum_bit = tmp_bit + index_val_1 + index_val_2;
    switch (sum_bit)
    {
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
  printf("mul sign %d\n", tmp.sign);
  *res = copy_long_Decimal(&tmp);
}

void sub_long_Decimal(const long_Decimal *val_1,const long_Decimal *val_2, long_Decimal *res){
  int tmp_bit = 0;
  long_Decimal invert_val_2; //, once;
  clear_long_Decimal(&invert_val_2);
  //clear_long_Decimal(&once);
  clear_long_Decimal(res);
  for (int i = 0; i < 6; ++i) {
    invert_val_2.bits[i] = ~(val_2->bits[i]);
  }
  invert_val_2.bits[0] += 1;
  //once.bits[0] = 0;
  //add_long_Decimal(&invert_val_2, &once, &invert_val_2);
  add_long_Decimal(val_1, &invert_val_2, res);
  //add_long_Decimal(res, &once, res);

}

void clear_long_Decimal(long_Decimal *dst) {
  for (int i = 0; i < 6; ++i) {
    dst->bits[i] = 0;
  }
  dst->sign = 1;
  dst->exp_decimal = 0;
}

long_Decimal copy_long_Decimal(const long_Decimal *val){
  long_Decimal tmp;
  clear_long_Decimal(&tmp);
  for (int k = 0; k < 6;++k){
    tmp.bits[k] = val->bits[k];
  }
  tmp.exp_decimal = val->exp_decimal;
  tmp.sign = val->sign;
  return tmp;
}

int mul_long_Decimal(const long_Decimal *val_1,
                         const long_Decimal *val_2, long_Decimal *res){
  int offset_count = 0;
  long_Decimal tmp, val_1_copy;
  clear_long_Decimal(&tmp);
  val_1_copy = copy_long_Decimal(val_1);
   
  
  for (int i = 0; i < 192;++i){
    int arr = i / 32;
    int index_bit = i % 32;
    if((1<<index_bit)&val_2->bits[arr]){
      if(offset_mantissa_left(&val_1_copy, offset_count)==FAIL){
        return FAIL;
      }
      add_long_Decimal(&tmp, &val_1_copy, &tmp);
      offset_count = 1;
    } else{
      offset_count++;
    }
  }
  tmp.sign = val_1_copy.sign;
  *res = copy_long_Decimal(&tmp);
  return OK;
}

int offset_mantissa_left(long_Decimal *val, unsigned count) {
  for (int j = 0; j < count; ++j){
    if ((val->bits[5] & 0xA0000000) != 0) return FAIL;
  for (int i = 5; i > 0; i--) {
    val->bits[i] = (val->bits[i] << 1);
    if((val->bits[i-1]&0xA0000000)!=0) {
      val->bits[i] = (val->bits[i] | 1);
    }
  }
  val->bits[0] = (val->bits[0] << 1);
  }
  return OK;
}

int pow_mantissa(long_Decimal *val, unsigned n){
  long_Decimal prod;
  long_Decimal mult;
  clear_long_Decimal(&prod);
  prod.bits[0] = 1;
  mult = copy_long_Decimal(val);
  while (n > 0) {
    if(n%2==1) {
      if (mul_long_Decimal(&prod, &mult, &prod) == FAIL) return FAIL;
      n = n - 1;
    }else{
      if (mul_long_Decimal(&mult, &mult, &mult) == FAIL) return FAIL;
      n /= 2;
    }
  }
  *val = copy_long_Decimal(&prod);
  return OK;
}


