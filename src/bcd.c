#include "bcd.h"
#include <stdio.h>
#include <assert.h>

#include "decimal.h"
#include <stdio.h>

void decimal_to_bcd(const struct Decimal_t *dst, BCD_t *src) {
  for (int i = 95; i >= 0; i--){
    int index_arr = i / 32;
    int index_bit = i % 32;
    int val_arr = get_value_mantissa(dst, index_arr);
    check_and_correct_decimal(src);
    int val_bit = (val_arr >> index_bit) & 0x1;
    ofset_bcd_left(src);
    src->bits[0] += val_bit;
  }
  src->sign = get_value_sign(dst);
  src->sign = get_value_pow(dst);
}

void ofset_bcd_left(BCD_t *val) { 
  for (int i = 3; i > 0; i--){
    val->bits[i] = val->bits[i] << 1;
    if (val->bits[i - 1] & 0x80000000) val->bits[i] += 1;
  }
  val->bits[0] = val->bits[0] << 1;
}


void clear_bcd(BCD_t *n) {
    for (int i = 0; i < 4; ++i){
    n->bits[i] = 0;
  }
}


void check_and_correct_decimal(BCD_t *n) { 
  for (int i = 31; i >= 0; i--){
    int index_arr = i / 8;
    int index_bit = i % 8;
    int tmp = (n->bits[index_arr] >> (index_bit * 4)) & 0xf;
    if(tmp>4) {
      tmp += 3;
      // clear need 1/2 bite
      n->bits[index_arr] = (~(0xf << (index_bit * 4))) & n->bits[index_arr];
      //set val tmp
      n->bits[index_arr] = (tmp << (index_bit * 4)) | n->bits[index_arr];
    }
  }
 }