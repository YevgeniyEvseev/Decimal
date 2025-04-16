#include <stdio.h>

#include "bcd.h"
#include "decimal.h"
#include "string.h"
void printf_bit(unsigned n) {
  for (int i = 0; i < 32; ++i) {
    int res = (n >> i) & 1;
    printf("%d", res);
  }
  printf("\n");
}

int main() {
  int n;
  char res[36] = {0};
  struct Decimal_t *d1 = init_decimal();
  int res1 = ctor_string(d1, "-5.3");
  // print_decimal(d1);
  from_decimal_to_string(d1, res);
  printf("%s ", res);
  destroy_decimal(d1);
}