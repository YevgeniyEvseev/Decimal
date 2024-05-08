#include <assert.h>
#include "mantissa.h"
#include <stdio.h>

typedef struct {
  int bits[4];
} Decimal_t;


int add_decimal( Decimal_t const *val_1,  Decimal_t const *val_2,
         Decimal_t *res) {
  Decimal_mantissa new_val_1, new_val_2, res_mantissa;
  clear_decimal_mantissa(&new_val_1);
  clear_decimal_mantissa(&new_val_2);
  clear_decimal_mantissa(&res_mantissa);

  new_val_1.bits[0] = 34;
  new_val_2.bits[0] = 64;

  // align_decimal(val_1, val_2, new_val_1, new_val_2);
   add_decimal_mantissa(&new_val_1, &new_val_2, &res_mantissa);
   printf("%d", res_mantissa.bits[0]);
   // full_dec_to_decimal(res_mantissa, res);
}