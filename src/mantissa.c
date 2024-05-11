#include "mantissa.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


void add_decimal_mantissa(const Decimal_mantissa *val_1,const Decimal_mantissa *val_2, Decimal_mantissa *res){
  int tmp_bit = 0;
  Decimal_mantissa tmp;
  clear_decimal_mantissa(&tmp);
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
      assert("default add_decimal_mantissa");
      break;
    }
  }
  tmp.sign = val_1->sign;
  printf("mul sign %d\n", tmp.sign);
  *res = copy_decimal_mantissa(&tmp);
}

void sub_decimal_mantissa(const Decimal_mantissa *val_1,const Decimal_mantissa *val_2, Decimal_mantissa *res){
  int tmp_bit = 0;
  Decimal_mantissa invert_val_2; //, once;
  clear_decimal_mantissa(&invert_val_2);
  //clear_decimal_mantissa(&once);
  clear_decimal_mantissa(res);
  for (int i = 0; i < 6; ++i) {
    invert_val_2.bits[i] = ~(val_2->bits[i]);
  }
  invert_val_2.bits[0] += 1;
  //once.bits[0] = 0;
  //add_decimal_mantissa(&invert_val_2, &once, &invert_val_2);
  add_decimal_mantissa(val_1, &invert_val_2, res);
  //add_decimal_mantissa(res, &once, res);

}

void clear_decimal_mantissa(Decimal_mantissa *dst) {
  for (int i = 0; i < 6; ++i) {
    dst->bits[i] = 0;
  }
  dst->sign = 1;
  dst->exp_decimal = 0;
}

Decimal_mantissa copy_decimal_mantissa(const Decimal_mantissa *val){
  Decimal_mantissa tmp;
  clear_decimal_mantissa(&tmp);
  for (int k = 0; k < 6;++k){
    tmp.bits[k] = val->bits[k];
  }
  tmp.exp_decimal = val->exp_decimal;
  tmp.sign = val->sign;
  return tmp;
}

int mul_decimal_mantissa(const Decimal_mantissa *val_1,
                         const Decimal_mantissa *val_2, Decimal_mantissa *res){
  int offset_count = 0;
  Decimal_mantissa tmp, val_1_copy;
  clear_decimal_mantissa(&tmp);
  val_1_copy = copy_decimal_mantissa(val_1);
   
  
  for (int i = 0; i < 192;++i){
    int arr = i / 32;
    int index_bit = i % 32;
    if((1<<index_bit)&val_2->bits[arr]){
      if(offset_mantissa_left(&val_1_copy, offset_count)==FAIL){
        return FAIL;
      }
      add_decimal_mantissa(&tmp, &val_1_copy, &tmp);
      offset_count = 1;
    } else{
      offset_count++;
    }
  }
  tmp.sign = val_1_copy.sign;
  *res = copy_decimal_mantissa(&tmp);
  return OK;
}

int offset_mantissa_left(Decimal_mantissa *val, unsigned count) {
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

int pow_mantissa(Decimal_mantissa *val, unsigned n){
  Decimal_mantissa prod;
  Decimal_mantissa mult;
  clear_decimal_mantissa(&prod);
  prod.bits[0] = 1;
  mult = copy_decimal_mantissa(val);
  while (n > 0) {
    if(n%2==1) {
      if (mul_decimal_mantissa(&prod, &mult, &prod) == FAIL) return FAIL;
      n = n - 1;
    }else{
      if (mul_decimal_mantissa(&mult, &mult, &mult) == FAIL) return FAIL;
      n /= 2;
    }
  }
  *val = copy_decimal_mantissa(&prod);
  return OK;
}
