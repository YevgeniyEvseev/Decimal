#include "bcd.h"
#include "decimal.h"
#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

START_TEST(string_decimal_string) {
  char n[35] = "123456789";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string2) {
  char n[35] = "0";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string_max) {
  char n[35] = "79228162514264337593543950335";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string_error1) {
  char n[35] = "79228162514264337593543950336";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 1);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string3) {
  char n[35] = "792281625142643375935.43950336";
  char result[35] = "792281625142643375935.4395034";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  // printf("ddddddddd=%d\n", res);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(result, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string4) {
  char n[35] = " 79 228 162.5142";
  char n_r[35] = "79228162.5142";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  // printf("ddddddddd=%d\n", res);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n_r, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string5) {
  char n[35] = "-.5";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string6) {
  char n[35] = "-0.05";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  printf("exp=%d", get_value_pow(t));
  ck_assert_uint_eq(res, 0);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string7) {
  char n[35] = "-0.0000000000000000000000000002";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 0);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string_err2) {
  char n[35] = "-0.00000000000000000000000000001";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 1);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string_err3) {
  char n[35] = "-0.000000000000.00000000000001";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 1);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string_err4) {
  char n[35] = "--0.00000000000000000000000001";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 1);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(string_decimal_string_err5) {
  char n[35] = "-0.000000f000000000001";
  char n_res[35] = {0};
  struct Decimal_t *t = init_decimal();
  int res = from_string_to_decimal(n, t);
  ck_assert_uint_eq(res, 1);
  if (res == 0) {
    from_decimal_to_string(t, n_res);
    int res_cmp = strcmp(n, n_res);
    printf("string=%s\n", n_res);
    ck_assert_uint_eq(res_cmp, 0);
  }
}
END_TEST

START_TEST(add_1) {
  char n1[35] = "15";
  char n2[35] = "25";
  char n_res[35] = "40";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(add_2) {
  char n1[35] = "15";
  char n2[35] = "-25";
  char n_res[35] = "-10";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(add_3) {
  char n1[35] = "-15";
  char n2[35] = "-25";
  char n_res[35] = "-40";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(add_4) {
  char n1[35] = "-15";
  char n2[35] = "25";
  char n_res[35] = "10";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(add_5) {
  char n1[35] = "15.3456";
  char n2[35] = "25.12";
  char n_res[35] = "40.4656";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(add_6) {
  char n_res[35] = "1000000002000000.4656";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "1 000 000 000 000 000.3456");
  int res2 = ctor_string(d2, "2 000 000.12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST


START_TEST(add_1_err) {
  char n1[35] = "79228162514264337593543950335";
  char n2[35] = "10";
  //char n_res[35] = "1000000002000000.4656";
  //char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = from_string_to_decimal(n1, d1);
  int res2 = from_string_to_decimal(n2, d2);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=add_decimal(d1, d2, res_d);

  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(add_7) {
  char n_res[35] = "-0.000091";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-0.00009");
  int res2 = ctor_string(d2,"-0.000001");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  add_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(add_2_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"79228162514264337593543950335");
  int res2 = ctor_string(d2,"1");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=add_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(sub_1) {
  char n_res[35] = "111.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "123.1");
  int res2 = ctor_string(d2, "12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  sub_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(sub_2) {
  char n_res[35] = "135.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "123.1");
  int res2 = ctor_string(d2, "-12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  sub_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(sub_3) {
  char n_res[35] = "-111.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "-12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  sub_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(sub_4) {
  char n_res[35] = "-135.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  sub_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(sub_5) {
  char n_res[35] = "0.00999";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-0.00001");
  int res2 = ctor_string(d2, "-0.01");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  sub_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(sub_6) {
  char n_res[35] = "-.499";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.001");
  int res2 = ctor_string(d2, "0.5");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  sub_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_1) {
  char n_res[35] = "1477.2";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "123.1");
  int res2 = ctor_string(d2, "12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_2) {
  char n_res[35] = "-1477.2";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "123.1");
  int res2 = ctor_string(d2, "-12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_3) {
  char n_res[35] = "1477.2";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "-12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_4) {
  char n_res[35] = "-1477.2";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_5) {
  char n_res[35] = "0.0000001";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-0.00001");
  int res2 = ctor_string(d2, "-0.01");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_6) {
  char n_res[35] = "0.0005";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.001");
  int res2 = ctor_string(d2, "0.5");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_7) {
  char n_res[35] = "0";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.001");
  int res2 = ctor_string(d2, "0");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mul_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mul_1_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"79228162514264337593543950335");
  int res2 = ctor_string(d2,"2");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=mul_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(mul_2_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-79228162514264337593543950335");
  int res2 = ctor_string(d2,"2");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=mul_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(mul_3_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"0.00000000000000001");
  int res2 = ctor_string(d2,"0.00000000000000001");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=mul_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(mul_4_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-0.00000000000000001");
  int res2 = ctor_string(d2,"0.00000000000000001");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=mul_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST


START_TEST(div_1) {
  char n_res[35] = "25.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "125.5");
  int res2 = ctor_string(d2, "5");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_2) {
  char n_res[35] = "-2.5";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.1");
  int res2 = ctor_string(d2, "-0.04");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_3) {
  char n_res[35] = "10.258333333333333333333333334";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "-12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_4) {
  char n_res[35] = "-10.258333333333333333333333334";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_5) {
  char n_res[35] = "0.001";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-0.00001");
  int res2 = ctor_string(d2, "-0.01");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_6) {
  char n_res[35] = "0.002";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.001");
  int res2 = ctor_string(d2, "0.5");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_7) {
  char n_res[35] = "0";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0");
  int res2 = ctor_string(d2, "2");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_8) {
  char n_res[35] = ".3333333333333333333333333333";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "1");
  int res2 = ctor_string(d2, "3");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  div_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(div_1_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"79228162514264337593543950335");
  int res2 = ctor_string(d2,"0.2");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=div_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(div_2_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-79228162514264337593543950335");
  int res2 = ctor_string(d2,"0.2");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=div_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(div_3_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"0.00000000000000001");
  int res2 = ctor_string(d2,"10000000000000000000");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=div_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(div_4_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-0.00000000000000001");
  int res2 = ctor_string(d2,"10000000000000000000");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=div_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 1);
}
END_TEST

START_TEST(div_5_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-0.00000000000000001");
  int res2 = ctor_string(d2,"0");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=div_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 2);
}
END_TEST


START_TEST(mod_1) {
  char n_res[35] = ".5";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "125.5");
  int res2 = ctor_string(d2, "5");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_2) {
  char n_res[35] = "-0.02";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.1");
  int res2 = ctor_string(d2, "-0.04");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_3) {
  char n_res[35] = "3.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "-12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_4) {
  char n_res[35] = "-3.1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-123.1");
  int res2 = ctor_string(d2, "12");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_5) {
  char n_res[35] = "0.00001";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "-0.00001");
  int res2 = ctor_string(d2, "-0.01");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_6) {
  char n_res[35] = "0.001";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0.001");
  int res2 = ctor_string(d2, "0.5");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_7) {
  char n_res[35] = "0";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "0");
  int res2 = ctor_string(d2, "2");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_8) {
  char n_res[35] = "1";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1, "1");
  int res2 = ctor_string(d2, "3");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST


START_TEST(mod_10) {  
  char n_res[35] = "-.2";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-79228162514264337593543950334");
  int res2 = ctor_string(d2,"0.3");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

START_TEST(mod_11) {  
  char n_res[35] = "0.00000000000000001";
  char n[35] = {0};
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"0.00000000000000001");
  int res2 = ctor_string(d2,"10000000000000000000");
   ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  mod_decimal(d1, d2, res_d);

  from_decimal_to_string(res_d, n);
  int res_cmp = strcmp(n, n_res);
  printf("string=%s\n", n);
  ck_assert_uint_eq(res_cmp, 0);
}
END_TEST



START_TEST(mod_5_err) {  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  struct Decimal_t *res_d = init_decimal();
  int res1 = ctor_string(d1,"-0.00000000000000001");
  int res2 = ctor_string(d2,"0");
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(res2, 0);
  int err=mod_decimal(d1, d2, res_d);
  ck_assert_uint_eq(err, 2);
}
END_TEST

START_TEST(int_1) {
  int n_res = 123;
  int n=0;
  struct Decimal_t *d1 = init_decimal();
  int res1 = ctor_string(d1, "123.23");
  from_decimal_to_int(d1, &n);
  ck_assert_uint_eq(res1, 0);
  ck_assert_uint_eq(n_res, n);
}
END_TEST

START_TEST(comp_1) {
  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  int res1 = ctor_string(d1, "123.23");
  int res2 = ctor_string(d2, "123.23");
  ck_assert_uint_eq(is_equal(d1, d2), 1);
  ck_assert_uint_eq(is_not_equal(d1, d2), 0);
  ck_assert_uint_eq(is_greater (d1, d2), 0);
  ck_assert_uint_eq(is_greater_or_equal(d1, d2), 1);
  ck_assert_uint_eq(is_less(d1, d2), 0);
  ck_assert_uint_eq(is_less_or_equal(d1, d2), 1);
}
END_TEST

START_TEST(comp_2) {
  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  int res1 = ctor_string(d1, "12223212123122321.23");
  int res2 = ctor_string(d2, "123.23");
  ck_assert_uint_eq(is_equal(d1, d2), 0);
  ck_assert_uint_eq(is_not_equal(d1, d2), 1);
  ck_assert_uint_eq(is_greater (d1, d2), 1);
  ck_assert_uint_eq(is_greater_or_equal(d1, d2), 1);
  ck_assert_uint_eq(is_less(d1, d2), 0);
  ck_assert_uint_eq(is_less_or_equal(d1, d2), 0);
}
END_TEST


START_TEST(comp_3) {
  
  struct Decimal_t *d1 = init_decimal();
  struct Decimal_t *d2 = init_decimal();
  int res1 = ctor_string(d1, "12254675673122321.23");
  int res2 = ctor_string(d2, "1233242342342342332.232");
  ck_assert_uint_eq(is_equal(d1, d2), 0);
  ck_assert_uint_eq(is_not_equal(d1, d2), 1);
  ck_assert_uint_eq(is_greater (d1, d2), 0);
  ck_assert_uint_eq(is_greater_or_equal(d1, d2), 0);
  ck_assert_uint_eq(is_less(d1, d2), 1);
  ck_assert_uint_eq(is_less_or_equal(d1, d2), 1);
}
END_TEST

Suite *calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("CalcTest");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, string_decimal_string);
  tcase_add_test(tc_core, string_decimal_string2);
  tcase_add_test(tc_core, string_decimal_string_max);
  tcase_add_test(tc_core, string_decimal_string_error1);
  tcase_add_test(tc_core, string_decimal_string3);
  tcase_add_test(tc_core, string_decimal_string4);
  tcase_add_test(tc_core, string_decimal_string5);
  tcase_add_test(tc_core, string_decimal_string6);
  tcase_add_test(tc_core, string_decimal_string7);
  tcase_add_test(tc_core, string_decimal_string_err2);
  tcase_add_test(tc_core, string_decimal_string_err3);
  tcase_add_test(tc_core, string_decimal_string_err4);
  tcase_add_test(tc_core, string_decimal_string_err5);
  tcase_add_test(tc_core, add_1);
  tcase_add_test(tc_core, add_2);
  tcase_add_test(tc_core, add_3);
  tcase_add_test(tc_core, add_4);
  tcase_add_test(tc_core, add_5);
  tcase_add_test(tc_core, add_6);
  tcase_add_test(tc_core, add_1_err);
  tcase_add_test(tc_core, add_7);
  tcase_add_test(tc_core, add_2_err);
  tcase_add_test(tc_core, sub_1);
  tcase_add_test(tc_core, sub_2);
  tcase_add_test(tc_core, sub_3);
  tcase_add_test(tc_core, sub_4);
  tcase_add_test(tc_core, sub_5);
  tcase_add_test(tc_core, sub_6);
  tcase_add_test(tc_core, mul_1);
  tcase_add_test(tc_core, mul_2);
  tcase_add_test(tc_core, mul_3);
  tcase_add_test(tc_core, mul_4);
  tcase_add_test(tc_core, mul_5);
  tcase_add_test(tc_core, mul_6);
  tcase_add_test(tc_core, mul_7);
  tcase_add_test(tc_core, mul_1_err);
  tcase_add_test(tc_core, mul_2_err);
  tcase_add_test(tc_core, mul_3_err);
  tcase_add_test(tc_core, mul_4_err);
  tcase_add_test(tc_core, div_1);
  tcase_add_test(tc_core, div_2);
  tcase_add_test(tc_core, div_3);
  tcase_add_test(tc_core, div_4);
  tcase_add_test(tc_core, div_5);
  tcase_add_test(tc_core, div_6);
  tcase_add_test(tc_core, div_7);
  tcase_add_test(tc_core, div_8);
  tcase_add_test(tc_core, div_1_err);
  tcase_add_test(tc_core, div_2_err);
  tcase_add_test(tc_core, div_3_err);
  tcase_add_test(tc_core, div_4_err);
  tcase_add_test(tc_core, div_5_err);
  tcase_add_test(tc_core, mod_1);
  tcase_add_test(tc_core, mod_2);
  tcase_add_test(tc_core, mod_3);
  tcase_add_test(tc_core, mod_4);
  tcase_add_test(tc_core, mod_5);
  tcase_add_test(tc_core, mod_6);
  tcase_add_test(tc_core, mod_7);
  tcase_add_test(tc_core, mod_8);
 
  tcase_add_test(tc_core, mod_10);
  tcase_add_test(tc_core, mod_11);
  tcase_add_test(tc_core, mod_5_err);
  tcase_add_test(tc_core, int_1);
  tcase_add_test(tc_core, comp_1);
  tcase_add_test(tc_core, comp_2);
  tcase_add_test(tc_core, comp_3);

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  Suite *s = calc_suite();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_NORMAL);
  int no_failed = srunner_ntests_failed(runner);
  srunner_free(runner);
  return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}