#ifndef MANTISSA_H
#define MANTISSA_H

typedef struct {
  int bits[6];
  int sign;
  int exp_decimal;
} Decimal_mantissa;

void clear_decimal_mantissa(Decimal_mantissa *val);
int add_decimal_mantissa(const Decimal_mantissa *val_1,
                         const Decimal_mantissa *val_2, Decimal_mantissa *res);
int sub_decimal_mantissa(const Decimal_mantissa *val_1,
                         const Decimal_mantissa *val_2, Decimal_mantissa *res);

#endif