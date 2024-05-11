#ifndef MANTISSA_H
#define MANTISSA_H

#define FAIL 0
#define OK 1

typedef struct {
  int bits[6];
  int sign;
  int exp_decimal;
} Decimal_mantissa;

void clear_decimal_mantissa(Decimal_mantissa *val);
Decimal_mantissa copy_decimal_mantissa(const Decimal_mantissa *val);
void add_decimal_mantissa(const Decimal_mantissa *val_1,
                          const Decimal_mantissa *val_2, Decimal_mantissa *res);
void sub_decimal_mantissa(const Decimal_mantissa *val_1,
                         const Decimal_mantissa *val_2, Decimal_mantissa *res);

int mul_decimal_mantissa(const Decimal_mantissa *val_1,
                         const Decimal_mantissa *val_2, Decimal_mantissa *res);

int pow_mantissa(Decimal_mantissa *val, unsigned n);

int offset_mantissa_left(Decimal_mantissa *val, unsigned count);

#endif