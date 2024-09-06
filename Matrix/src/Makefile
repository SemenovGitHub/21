CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
LDFLAGS = -lcheck -pthread -lm -lsubunit 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
TARGET = s21_matrix.a
TESTS = s21_tests
CFOLD = cov_fold
SRC_DIRS = Basic Additional 
OBJ_DIR = obj
SRC_EXT = .c
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*$(SRC_EXT)))
OBJ_FILES = $(patsubst %$(SRC_EXT),$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))
COV_OBJECT_FILES = $(patsubst %$(SRC_EXT),$(CFOLD)/%_coverage.o,$(notdir $(SRC_FILES)))


all: clean $(TARGET)

test: clean s21_matrix.a $(TESTS)/s21_test.h
	gcc -o s21_tests.out $(TESTS)/*.c -L. -l:s21_matrix.a $(CFLAGS) $(LDFLAGS) 

clang:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -n {} \;

# main.out: main.c $(OBJ_FILES)
#	$(CC) $(CFLAGS) -o $@ $< $(OBJ_DIR)/*.o -lm

val: clean main.out
	valgrind --tool=memcheck --leak-check=yes ./main.out

test_val: clean test 
	valgrind --tool=memcheck --leak-check=yes ./s21_tests.out
	
s21_matrix_tests_cov: s21_matrix_cov.a $(TESTS)/*.c
	gcc $(GCOV_FLAGS) $(GFLAGS) $^ -o $@ $(LDFLAGS) $<


gcov_report: s21_matrix_tests_cov
	./$<
	lcov --directory $(shell pwd) -c -o coverage.info
	mkdir -p html
	genhtml -o html coverage.info


s21_matrix.a: $(OBJ_FILES)
	ar crs $@ $(OBJ_DIR)/*.o

s21_matrix_cov.a: $(COV_OBJECT_FILES)
	ar rcs $@ $(CFOLD)/*.o
	ranlib $@

$(OBJ_DIR)/%.o: Additional/%.c  s21_matrix.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@ 
	
$(OBJ_DIR)/%.o: Basic/%.c  s21_matrix.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@ 


# Coverage 

$(CFOLD)/%_coverage.o: Additional/%.c  s21_matrix.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@  
	
$(CFOLD)/%_coverage.o: Basic/%.c  s21_matrix.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@ 

ofolder:
	mkdir -p $(OBJ_DIR)

covfolder:
	mkdir -p $(CFOLD)

clean:
	rm -f $(OBJ_FILES) *.a main.o *.out *.gch *.gcno *.gcda $(COV_OBJECT_FILES) *.info s21_matrix_tests_cov s21_matrix
	rm -rf html cov_fold obj report