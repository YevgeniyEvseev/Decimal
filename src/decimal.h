#ifndef DECIMAL_H
#define DECIMAL_H



#include "mantissa.h"

struct Decimal_t;


struct Decimal_t *init_decimal();
int ctor_int(struct Decimal_t *dst, int n);
int ctor_double(struct Decimal_t *dst, double n);
int ctor_string(struct Decimal_t *dst, const char *n);

void set_bit_decimal(struct Decimal_t *dst, int number_bit);

void clear_decimal(struct Decimal_t *dst);

//convert decimal to long_Decimal with align float point
int align_exp_mantissa(const struct Decimal_t *val_1,
                       const struct Decimal_t *val_2,
                       long_Decimal *new_val_1,
                       long_Decimal *new_val_2);
int get_value_pow(struct Decimal_t const *val);
void set_value_pow(struct Decimal_t *des, int val);

// set sign decimal 1-positiv (-1)-negative
void set_value_sign(struct Decimal_t *des, int val);

// get sign decimal 1-positiv (-1) -negative
int get_value_sign(struct Decimal_t const *val);

//return 0 =- OK     1- error size answer 
int add_decimal(struct Decimal_t const *val_1, struct Decimal_t const *val_2,
        struct Decimal_t *res);
        //return 0 =- OK     1- error size answer 
int sub_decimal(struct Decimal_t const *val_1, struct Decimal_t const *val_2,
        struct Decimal_t *res);
        //return 0 =- OK     1- error size answer 
int mul_decimal(struct Decimal_t const *val_1, struct Decimal_t const *val_2,
        struct Decimal_t *res);
//return 0 - OK    1- error size answer    2 - division 0
int div_decimal(const struct Decimal_t *value_1,
                 const struct Decimal_t *value_2, struct Decimal_t *result);

//return 0 - OK    1- error size answer    2 - division 0
int mod_decimal(const struct Decimal_t *value_1,
                 const struct Decimal_t *value_2, struct Decimal_t *result);

int is_null(const struct Decimal_t *n);

int from_decimal_to_float(struct Decimal_t const *src, float *dst);
int from_float_to_decimal(float src, struct Decimal_t *dst);
int from_decimal_to_int(struct Decimal_t const *src, int *dst);
int from_int_to_decimal(int src, struct Decimal_t *dst);
int from_string_to_decimal(const char *src, struct Decimal_t *dst);
int from_long_decimal_decimal(const long_Decimal *src, struct Decimal_t *dst);


int get_value_mantissa(const struct Decimal_t *val, unsigned index);

void set_value(struct Decimal_t *s, int val);

int mantisa_from_float(unsigned bit_float);
unsigned float_to_unsigned(float d);

void print_decimal(const struct Decimal_t *val);

int decimal_to_mantissa(const struct Decimal_t *src, long_Decimal *dst);
//int mantissa_to_decimal(const long_Decimal *src, struct Decimal_t *dst);

int is_less(struct Decimal_t*, struct Decimal_t*);
int is_less_or_equal(struct Decimal_t*, struct Decimal_t*);
int is_greater(struct Decimal_t*, struct Decimal_t*);
int is_greater_or_equal(struct Decimal_t*, struct Decimal_t*);
int is_equal(struct Decimal_t*, struct Decimal_t*);
int is_not_equal(struct Decimal_t*, struct Decimal_t*);

#endif