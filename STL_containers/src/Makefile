SHEL = /bin/sh 

CC = g++
CFLAGS = -g -Wall -Werror -Wextra -std=c++17
GTEST_FLAGS = -lgtest -lgtest_main -pthread -lpthread
GFLAGS = -lgtest -pthread -lstdc++ -lsupc++ -lgcc -lm
TEST_SRC = tests_nik/test.cpp
GCOV_DIR = gcov
ALL: test

test:clean
	$(CC) $(CFLAGS) $(TEST_SRC) -o test.run $(GFLAGS) 
	./test.run

gcov_report:
	mkdir -p $(GCOV_DIR)
	$(CC) $(CFLAGS) --coverage $(TEST_SRC) -o $(GCOV_DIR)/test_gcov.run $(GFLAGS)
	./$(GCOV_DIR)/test_gcov.run
	lcov --rc lcov_branch_coverage=1 --ignore-errors mismatch --capture --directory $(GCOV_DIR) --output-file $(GCOV_DIR)/coverage.info --exclude /usr/include
	genhtml $(GCOV_DIR)/coverage.info --output-directory $(GCOV_DIR)/out
	./$(GCOV_DIR)/out/index.html

clang:
	find . \( -name '*.tpp' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	find . \( -name '*.tpp' -o -name '*.h' \) -exec clang-format -n {} \;

clean:
	clear
	rm -rf *.run lib/linked_list/*.out $(GCOV_DIR)