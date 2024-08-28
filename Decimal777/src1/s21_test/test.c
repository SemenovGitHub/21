#include "test.h"

int main(void) {
  int num_failures = 0;

  Suite *test_suite[] = {test_add(),
                         test_sub(),
                         test_mul(),
                         test_div(),
                         test_is_less(),
                         test_is_less_or_equal(),
                         test_is_greater(),
                         test_is_greater_or_equal(),
                         test_is_equal(),
                         test_is_not_equal(),
                         test_from_int_to_decimal(),
                         test_from_float_to_decimal(),
                         test_from_decimal_to_int(),
                         test_from_decimal_to_float(),
                         test_floor(),
                         test_round(),
                         test_truncate(),
                         test_negate(),
                         NULL};

  for (int i = 0; test_suite[i] != NULL; ++i) {
    SRunner *runner = srunner_create(test_suite[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    num_failures += srunner_ntests_failed(runner);
    srunner_free(runner);
  }

  printf("========== NUMBER OF FAILURES: %d ==========\n", num_failures);
  return 0;
}