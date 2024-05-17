#include "bcd.h"
#include <stdio.h>
#include <assert.h>

void offset_BCD_left(struct BCD_format *val) {
  for (int i = 3; i > 0; i--) {
    val->bits[i] = (val->bits[i] << 1);
    if((val->bits[i-1]&0x80000000)!=0) {
      val->bits[i] = (val->bits[i] | 1);
    }
  }
  val->bits[0] = (val->bits[0] << 1);
}

void set_four_bit(int *n, int bit, int pos_quadro){
  int res = *n;
  for (int i = 0; i < 4; ++i) {
    int tmp = ((0x1 << i) & bit)?1:0;
    int pos = pos_quadro*4+i;
    if (tmp == 1){
      res = (1 << pos) | res;
    }else if(tmp == 0){
      res = (~(1 << pos)) & res;
    } else{
      assert("is not bit");
    }
  }
  *n = res;
}

void check_and_convert_bit(struct BCD_format* val){
  int count = 0;
  for (int i = 31; i >= 0; i--) {
    int index_arr = i / 8;
    int index_bit = i % 8;
    int tmp = ((val->bits[index_arr] >> index_bit * 4) & 0xf);
    
    if (tmp > 4) {
      count++;
      tmp += 3;
      set_four_bit(&val->bits[index_arr], tmp, index_bit);
      //offset_BCD_left(val);
      //i = 31;
    }
  }
  //printf("count %d", count);
}
