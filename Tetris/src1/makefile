CC := gcc
CFLAGS := -I brick_game/tetris/inc -std=c11 -Wall -Werror -Wextra -g
GCOV_FLAGS := -fprofile-arcs -ftest-coverage -lgcov
OBJS := brick_game/tetris/out/fsm_matrix.o
OBJS_FRONT := gui/cli/frontend.o
COV_OBJS := brick_game/tetris/out/fsm_matrix_coverage.o
COV_OBJS_FRONT := gui/cli/frontend_coverage.o

all: clean tetris

install: tetris
	mkdir game
	touch game/max_score.txt
	echo 0 > game/max_score.txt
	mv tetris game/

uninstall: clean
	rm -r game
	
tetris: main.o backend.a frontend.a
	$(CC) $(CFLAGS) $^ -o $@ -lncurses

dist: install
	zip -r game.zip game

dvi: clean
	doxygen Doxyfile
	open html/index.html

########################

brick_game/tetris/out/%.o: brick_game/tetris/src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 

%.o: gui/cli/%.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

backend.a: $(OBJS)
	ar crs $@ $(OBJS)

frontend.a: $(OBJS_FRONT)
	ar crs $@ $(OBJS_FRONT)

test: clean backend.a frontend.a 
	$(CC) $(CFLAGS) test/test.c -o tests -lcheck -lm -lsubunit -L. -l:backend.a -l:frontend.a -lncurses 
	./tests

#######################

brick_game/tetris/out/%_coverage.o: brick_game/tetris/src/%.c
	$(CC) $(CFLAGS) --coverage -c $< -o $@ 

gui/cli%_coverage.o: gui/cli/%.c
	$(CC) $(CFLAGS) --coverage -c $< -o $@

cov_backend.a: $(COV_OBJS)
	ar crs $@ $(COV_OBJS)

cov_frontend.a: $(COV_OBJS_FRONT)
	ar crs $@ $(COV_OBJS_FRONT)

test_cov: clean cov_backend.a cov_frontend.a 
	$(CC) $(GCOV_FLAGS) $(CFLAGS) test/test.c -o tests -lcheck -lm -lsubunit -L. -l:cov_backend.a -l:cov_frontend.a -lncurses 
	./tests

########################

gcov_report: clean test_cov
	lcov --directory $(shell pwd) -c -o coverage.info
	mkdir -p html
	genhtml -o html coverage.info
	open html/index.html

valgrind: all
	valgrind --tool=memcheck --leak-check=yes ./tetris

clang:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -i {} \;
	
clang_check:
	find . \( -name '*.c' -o -name '*.h' \) -exec clang-format -n {} \;

########################

clean:
	$(RM) brick_game/tetris/out/*.o gui/cli/*.o *.a *.o tetris
	$(RM) gui/cli/*.gcda gui/cli/*.gcno
	$(RM) brick_game/tetris/out/*.gcda brick_game/tetris/out/*.gcno
	$(RM) cov_backend.a cov_frontend.a
	$(RM) tests *.gcda *.gcno *.info
	$(RM) -rf html -r game game.zip -rf latex
