.PHONY: s21_string.a test gcov_report clean clang

CFLAGS = -std=c11 -Wall -Werror -Wextra
LDFLAGS = -lcheck -lcheck_pic -pthread -lm -lsubunit 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov

TESTS = s21_tests/test.c

STRING_FUNCTIONS = *.c

all: test 


s21_string.a: $(STRING_FUNCTIONS)
	gcc -c $(STRING_FUNCTIONS) $(CFLAGS)
	ar rcs s21_string.a *.o


test: s21_string.a
	gcc -o s21_test $(TESTS) -L. -l:s21_string.a $(CFLAGS) $(LDFLAGS)
	
	
valgrind_test: test
	valgrind --tool=memcheck --leak-check=yes --track-origins=yes --log-file=valgrind-out.txt ./s21_test

gcov_report: test
	gcc -o s21_test $(TESTS) -L. -l:s21_string.a $(CFLAGS) $(LDFLAGS) $(GCOV_FLAGS)
	./s21_test
	lcov -c -i -d . -o lcov_base.info
	lcov -c -d . -o lcov_test.info
	lcov --add-tracefile lcov_base.info --add-tracefile lcov_test.info --output-file lcov_total.info
	genhtml lcov_total.info --output-directory lcov_report_html --demangle-cpp --legend --title "Cpp basic gcov test"
	rm -f *.gcda *.gcno


clang:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov *.txt ./s21_test
	rm -rf lcov_report_html



