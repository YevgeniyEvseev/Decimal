#include <check.h>
#include "decimal.h"
#include <stdlib.h>
#include <stdio.h>
#include "bcd.h"
#include <string.h>

START_TEST(string_decimal_string) {
   char n[35] = "123456789";
   char n_res[35] = {0};
   struct Decimal_t *t = init_decimal();
   int res = from_string_to_decimal(n, t);
   ck_assert_uint_eq(res, 0);
   if(res==0){
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
   if(res==0){
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
   if(res==0){
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
   char result[35] = "792281625142643375935.4395033";
   char n_res[35] = {0};
   struct Decimal_t *t = init_decimal();
   int res = from_string_to_decimal(n, t);
   ck_assert_uint_eq(res, 0);
   //printf("ddddddddd=%d\n", res);
   if (res == 0) {
     from_decimal_to_string(t, n_res);
     int res_cmp = strcmp(result, n_res);
     printf("string=%s\n", n_res);
     ck_assert_uint_eq(res_cmp, 0);
   }
}
END_TEST

START_TEST(string_decimal_string4) {
   char n[35] = "79228162.5142";
   char n_res[35] = {0};
   struct Decimal_t *t = init_decimal();
   int res = from_string_to_decimal(n, t);
   ck_assert_uint_eq(res, 0);
   //printf("ddddddddd=%d\n", res);
   if (res == 0) {
     from_decimal_to_string(t, n_res);
     int res_cmp = strcmp(n, n_res);
     printf("string=%s\n", n_res);
     ck_assert_uint_eq(res_cmp, 0);
   }
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