#ifndef DECIMAL_H
#define DECIMAL_H



#include "mantissa.h"

struct Decimal_t;


struct Decimal_t *init_decimal();

void set_bit_decimal(struct Decimal_t *dst, int number_bit);

void clear_decimal(struct Decimal_t *dst);

//convert decimal to long_Decimal with align float point
int align_exp_mantissa(const struct Decimal_t *val_1,
                       const struct Decimal_t *val_2,
                       long_Decimal *new_val_1,
                       long_Decimal *new_val_2);
int get_value_pow(struct Decimal_t const *val);
void set_velue_pow(struct Decimal_t *des, int val);

// set sign decimal 1-positiv (-1)-negative
void set_velue_sign(struct Decimal_t *des, int val);

// get sign decimal 1-positiv (-1) -negative
int get_value_sign(struct Decimal_t const *val);
int add_decimal(struct Decimal_t const *val_1, struct Decimal_t const *val_2,
        struct Decimal_t *res);
int sub_decimal(struct Decimal_t const *val_1, struct Decimal_t const *val_2,
        struct Decimal_t *res);
//int div_decimal(const struct Decimal_t *value_1,
//                const struct Decimal_t *value_2, struct Decimal_t *result);

int from_decimal_to_float(struct Decimal_t const *src, float *dst);
int from_float_to_decimal(float src, struct Decimal_t *dst);
int from_decimal_to_int(struct Decimal_t const *src, int *dst);
int from_int_to_decimal(int src, struct Decimal_t *dst);
int from_string_to_decimal(const char *src, struct Decimal_t *dst);
int from_decimal_to_string(const struct Decimal_t *src, char *dst);


void set_value(struct Decimal_t *s, int val);

int mantisa_from_float(unsigned bit_float);
unsigned float_to_unsigned(float d);

void print_decimal(const struct Decimal_t *val);

int decimal_to_mantissa(const struct Decimal_t *src, long_Decimal *dst);
int mantissa_to_decimal(const long_Decimal *src, struct Decimal_t *dst);


#endif