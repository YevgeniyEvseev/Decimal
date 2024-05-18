
#include "decimal.h"
#include <stdio.h>
#include "bcd.h"
void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i){
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
  
struct Decimal_t *t = init_decimal();
  char n[20] = {"-12345678.91"};
  int res=from_string_to_decimal(n, t);
  char res_s[35] = {0};
 // BCD_t tmp;
 // clear_bcd(&tmp);

  //decimal_to_bcd(t, &tmp);

 // printf("test bcd\n");
  from_decimal_to_string(t, res_s);
  printf("%s\n", res_s);
  //printf("%x%x\n", tmp.bits[1], tmp.bits[0]);
}