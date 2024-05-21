#include "bcd.h"
#include <stdio.h>
#include <assert.h>

#include "decimal.h"
#include <stdio.h>

void decimal_to_bcd(const struct Decimal_t *dst, BCD_t *src) {
  clear_bcd(src);
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
  src->exp = get_value_pow(dst);
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

 void from_decimal_to_string(const struct Decimal_t *src, char *dst){
  if(is_null(src)==OK) {
    dst[0] = '0';
    return;
  }
  BCD_t tmp;
  int index_dst = 0, flag_null=0, len_str=0; 
  decimal_to_bcd(src, &tmp);
  int exp = tmp.exp;
  if(tmp.sign==-1){
    dst[index_dst++] = '-';
  }
  for (int i = 31; i >= 0; i--){
    int arr = i / 8;
    int i_bit = i % 8;
    int c = (tmp.bits[arr] >> i_bit*4) & 0xf;
    if(c!=0){
      flag_null = 1;
    }
    //пропускаем не значищушие нули
    if(c==0 && flag_null==0) continue;
    len_str++;
    dst[index_dst++] = '0' + c;
  }
  if(exp>1){
    char c ='.';
    for (int i = len_str - exp+1; i <= len_str+1; ++i){
      char tmp=dst[i];
      dst[i] = c;
      c = tmp;
    }
  }
}