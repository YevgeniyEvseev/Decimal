#include "mantissa.h"
#include <assert.h>
#include <stdlib.h>


int add_decimal_mantissa(const Decimal_mantissa *val_1,const Decimal_mantissa *val_2, Decimal_mantissa *res){
  int tmp_bit = 0;
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
      res->bits[arr] = (1 << index_bit) | res->bits[arr];
      break;
    case 2:
      tmp_bit = 1;
      break;
    case 3:
      tmp_bit = 1;
      res->bits[arr] = (1 << index_bit) | res->bits[arr];
      break;

    default:
      assert("default add_decimal_mantissa");
      break;
    }
  }
}

int sub_decimal_mantissa(const Decimal_mantissa *val_1,const Decimal_mantissa *val_2, Decimal_mantissa *res){
  int tmp_bit = 0;
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
      res->bits[arr] = (1 << index_bit) | res->bits[arr];
      break;
    case 2:
      tmp_bit = 1;
      break;
    case 3:
      tmp_bit = 1;
      res->bits[arr] = (1 << index_bit) | res->bits[arr];
      break;

    default:
      assert("default add_decimal_mantissa");
      break;
    }
  }
}

void clear_decimal_mantissa(Decimal_mantissa *dst) {
  for (int i = 0; i < 6; ++i) {
    dst->bits[i] = 0;
  }
  dst->sign = 0;
  dst->exp_decimal = 0;
}