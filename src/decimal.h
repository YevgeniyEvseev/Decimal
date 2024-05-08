#ifndef DECIMAL_H
#define DECIMAL_H

#include "mantissa.h"

struct Decimal_t;

struct Decimal_t *init_decimal();

void set_bit_decimal(struct Decimal_t *dst, int number_bit);

void clear_decimal(struct Decimal_t *dst);

int get_value_pow(struct Decimal_t const *val);
void set_velue_pow(struct Decimal_t *des, int val);

// set sign decimal 0-positiv 1-negative
void set_velue_sign(struct Decimal_t *des, int val);

// get sign decimal 0-positiv 1-negative
int get_value_sign(struct Decimal_t const *val);
int add_decimal(struct Decimal_t const *val_1, struct Decimal_t const *val_2,
        struct Decimal_t *res);
//int div_decimal(const struct Decimal_t *value_1,
//                const struct Decimal_t *value_2, struct Decimal_t *result);

int from_decimal_to_float(struct Decimal_t const *src, float *dst);

int from_float_to_decimal(float src, struct Decimal_t *dst);

void set_value(struct Decimal_t *s, int val);

int mantisa_from_float(unsigned bit_float);
unsigned float_to_unsigned(float d);

void print_decimal(const struct Decimal_t *val);

#endif