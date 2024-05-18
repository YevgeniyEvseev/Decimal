#include <check.h>
#include "decimal.h"
#include <stdlib.h>
#include <stdio.h>

START_TEST(test_new_calc) {
  
} END_TEST

Suite *calc_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("CalcTest");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_new_calc);
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