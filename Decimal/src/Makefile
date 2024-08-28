CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS = -lcheck -lcheck_pic -pthread -lm -lsubunit 
GCOV_FLAGS = -fprofile-arcs -ftest-coverage -lgcov
TARGET = s21_decimal.a
TESTS = s21_test
CFOLD = cov_fold

# Указываем директории с исходными файлами
SRC_DIRS = Additional Arithmetic Conversion Comparison Other

# Указываем директорию для объектных файлов
OBJ_DIR = obj

# Указываем расширения исходных файлов
SRC_EXT = .c


all: clean $(TARGET)

test: clean s21_decimal.a $(TESTS)/test.h
	gcc -o s21_tests $(TESTS)/*.c -L. -l:s21_decimal.a $(CFLAGS) $(LDFLAGS) 

clang:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -n {} \;


# Находим все исходные файлы
SRC_FILES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*$(SRC_EXT)))

# Находим все объектные файлы
OBJ_FILES = $(patsubst %$(SRC_EXT),$(OBJ_DIR)/%.o,$(notdir $(SRC_FILES)))

COV_OBJECT_FILES = $(patsubst %$(SRC_EXT),$(CFOLD)/%_coverage.o,$(notdir $(SRC_FILES)))

s21_decimal_tests_cov: s21_decimal_cov.a $(TESTS)/*.c
	gcc $(GCOV_FLAGS) $(GFLAGS) $^ -o $@ $(LDFLAGS) $<


gcov_report: s21_decimal_tests_cov
	./$<
	lcov --directory $(shell pwd) -c -o coverage.info
	mkdir -p html
	genhtml -o html coverage.info


s21_decimal.a: $(OBJ_FILES)
	ar crs $@ $(OBJ_DIR)/*.o

s21_decimal_cov.a: $(COV_OBJECT_FILES)
	ar rcs $@ $(CFOLD)/*.o
	ranlib $@

# gcc $(GFLAGS) -o $@ main.o -L. -l:s21_decimal.a

# Правило для создания объектных файлов. 
# Для каждой папки в которой есть файлы, нужно использовать:
#
# $(OBJ_DIR)/%.o: Имя_папки/%.c
# 	mkdir -p $(OBJ_DIR)
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: Additional/%.c  s21_decimal.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@ 
	
$(OBJ_DIR)/%.o: Arithmetic/%.c  s21_decimal.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)/%.o: Comparison/%.c s21_decimal.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)/%.o: Conversion/%.c s21_decimal.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@ 

$(OBJ_DIR)/%.o: Other/%.c s21_decimal.h ofolder
	$(CC) $(CFLAGS) -c $< -o $@

# Coverage 

$(CFOLD)/%_coverage.o: Additional/%.c  s21_decimal.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@  
	
$(CFOLD)/%_coverage.o: Arithmetic/%.c  s21_decimal.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@ 

$(CFOLD)/%_coverage.o: Comparison/%.c s21_decimal.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@  

$(CFOLD)/%_coverage.o: Conversion/%.c s21_decimal.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@

$(CFOLD)/%_coverage.o: Other/%.c s21_decimal.h covfolder
	$(CC) $(CFLAGS) --coverage -c $< -o $@ 

ofolder:
	mkdir -p $(OBJ_DIR)

covfolder:
	mkdir -p $(CFOLD)

clean:
	rm -f $(OBJ_FILES) *.a main.o *.out *.gch *.gcno *.gcda s21_tests $(COV_OBJECT_FILES) *.info s21_decimal_tests_cov s21_decimal
	rm -rf html cov_fold obj report