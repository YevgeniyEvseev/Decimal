#ifndef DECIMAL_DEF_H
#define DECIMAL_DEF_H

#define SIZE_DECIMAL 96
#define SIZE_NIBBLE 4
#define FALSE 0
#define TRUE 1
#define CRITICAL 0
#define WARNING 1

#define ERR_1(STR) fprintf(stderr, "%s %d %s", __FILE__, __LINE__, STR)

#define ERR_2(STR, SERV)                                  \
  do {                                                    \
    fprintf(stderr, "%s %d %s", __FILE__, __LINE__, STR); \
    if (!SERV) {                                          \
      fprintf(stderr, "aborting....");                    \
      abort();                                            \
    }                                                     \
  } while (0)

#define GET_3D_ARGS(A1, A2, A3, ...) A3
#define MACRO_CHOOSER(...) GET_3D_ARGS(__VA_ARGS__, ERR_2, ERR_1)
#define ERROR(...) MACRO_CHOOSER(__VA_ARGS__)(__VA_ARGS__)

typedef int bool_t;

typedef struct {
  int bit[4];
} Decimal_t;

typedef struct {
  unsigned bit[4];
} BCD_t;

void Decimal_to_BCD(BCD_t *dest, Decimal_t *src);
void BCD_to_Decimal(Decimal_t *dest, BCD_t *src);
int get_nibble(BCD_t *value, int n);
int get_decimal_bit(Decimal_t *value, int n);
void correrct_nibble(BCD_t *value, int n);
void empty_bit(void *value);
void offset_bit(BCD_t *value);

#endif