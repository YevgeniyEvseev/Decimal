
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
  
char n[35] = "79228162514264337593543950336";
   char n_res[35] = {0};
   struct Decimal_t *t = init_decimal();
   int res = from_string_to_decimal(n, t);
   
}