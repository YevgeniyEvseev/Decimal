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
  // printf("ddddddddd=%d\n", res);
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
  char n1[35] = "1 000 000 000 000 000.3456";
  char n2[35] = "2 000 000.12";
  char n_res[35] = "1000000002000000.4656";
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