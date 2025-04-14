#ifndef DECIMAL_H
#define DECIMAL_H

struct Decimal_t;

/*
bits[0], bits[1], and bits[2] contain the low, middle, and high 32 bits of the
96-bit integer number accordingly. bits[3] contains the scale factor and sign,
and consists of following parts:

Bits 0 to 15, the lower word, are unused and must be zero.
Bits 16 to 23 must contain an exponent between 0 and 28, which indicates the
power of 10 to divide the integer number. Bits 24 to 30 are unused and must be
zero. Bit 31 contains the sign; 0 meaning positive, and 1 meaning negative.*/

struct Decimal_t *init_decimal();

void print_decimal(struct Decimal_t *value);

int decimal_add(struct Decimal_t *value_1, struct Decimal_t *value_2,
                struct Decimal_t *result);
void decimal_to_str(struct Decimal_t *value, char *str);

int get_sign_decimal(struct Decimal_t *value);
int get_degree_decimal(struct Decimal_t *value);
void set_sign_decimal(struct Decimal_t *value, int sign);
void set_degree_decimal(struct Decimal_t *value, int degree);

#endif