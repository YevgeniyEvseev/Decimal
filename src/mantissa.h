#ifndef MANTISSA_H
#define MANTISSA_H

#define FAIL 0
#define OK 1

typedef struct {
  int bits[6];
  int sign;
  int exp_decimal;
} long_Decimal;


int get_decimal_bit(const long_Decimal *n, int index_bit);

void clear_long_Decimal(long_Decimal *val);
long_Decimal copy_long_Decimal(const long_Decimal *val);
void add_long_Decimal(const long_Decimal *val_1,
                          const long_Decimal *val_2, long_Decimal *res);
void sub_long_Decimal(const long_Decimal *val_1,
                         const long_Decimal *val_2, long_Decimal *res);

int mul_long_Decimal(const long_Decimal *val_1,
                         const long_Decimal *val_2, long_Decimal *res);

int div_long_Decimal(const long_Decimal *val_1, const long_Decimal *val_2,
                     long_Decimal *res, long_Decimal *mod);

int pow_mantissa(long_Decimal *val, unsigned n);

int offset_mantissa_left(long_Decimal *val, unsigned count);

//int is_null(const long_Decimal *n);
//0 if val_1=val_2  1 if val_1>val_2  -1 if val_1<val_2
int cmp_long_decimal(const long_Decimal *val_1, const long_Decimal *val_2);

#endif