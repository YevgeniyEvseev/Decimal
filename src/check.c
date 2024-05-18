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
   from_decimal_to_string(t, n_res);
   ck_assert_uint_eq(res, 0);
   int res_cmp = strcmp(n, n_res);
   printf("%s\n", n_res);
   ck_assert_uint_eq(res_cmp, 0);
}
END_TEST

Suite *calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("CalcTest");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, string_decimal_string);
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