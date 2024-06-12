SHELL := /bin/bash

FILE = text.txt

FILE2 = text2.txt

CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra

CHECK = 2>&1 valgrind --tool=memcheck --leak-check=yes

all : s21_grep

s21_grep : s21_grep.o func_grep.o
	$(CC) $(CFLAGS) $^ -o $@

s21_grep.o : s21_grep.c func_grep.h
	$(CC) $(CFLAGS) -c $< -o $@

func-grep.o : func_grep.c func_grep.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f *.o s21_grep
    
rebuild : clean all

tests : 
	 -diff <(./s21_grep -e the $(FILE)) <(grep -e the $(FILE))
	 -diff <(./s21_grep -i THE $(FILE)) <(grep -i THE $(FILE))
	 -diff <(./s21_grep -v the $(FILE)) <(grep -v the $(FILE))
	 -diff <(./s21_grep -c the $(FILE) $(FILE2)) <(grep -c the $(FILE) $(FILE2))
	 -diff <(./s21_grep -l the $(FILE) $(FILE2)) <(grep -l the $(FILE) $(FILE2))
	 -diff <(./s21_grep -n the $(FILE) $(FILE2)) <(grep -n the $(FILE) $(FILE2))
	 -diff <(./s21_grep -h the $(FILE) $(FILE2)) <(grep -h the $(FILE) $(FILE2))
	 -diff <(./s21_grep -s лдвалд $(FILE)) <(grep -s лдвалд $(FILE))
	 -diff <(./s21_grep -hn the $(FILE)) <(grep -hn the $(FILE))

	$(CHECK) ./s21_grep -e the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -i THE $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -v the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -c the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -n the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -l the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -h the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -s the $(FILE) | grep ERROR
	$(CHECK) ./s21_grep -hn the $(FILE) | grep ERROR
	
	
.PHONY: tests