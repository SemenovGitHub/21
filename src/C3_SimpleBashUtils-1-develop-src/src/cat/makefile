SHELL := /bin/bash

FILE = text.txt

CC = gcc

CFLAGS = -std=c11 -Wall -Werror -Wextra

CHECK = 2>&1 valgrind --tool=memcheck --leak-check=yes

all : s21_cat

s21_cat : s21_cat.o func.o
	$(CC) $(CFLAGS) $^ -o $@

s21_cat.o : s21_cat.c func.h
	$(CC) $(CFLAGS) -c $< -o $@

func.o : func.c func.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f *.o s21_cat
    
rebuild : clean all

tests : 
	 -diff <(./s21_cat $(FILE)) <(cat $(FILE))
	 -diff <(./s21_cat -e $(FILE)) <(cat -e $(FILE))
	 -diff <(./s21_cat -t $(FILE)) <(cat -t $(FILE))
	 -diff <(./s21_cat -s $(FILE)) <(cat -s $(FILE))
	 -diff <(./s21_cat --squeeze-blank $(FILE)) <(cat --squeeze-blank $(FILE))
	 -diff <(./s21_cat -n $(FILE)) <(cat -n $(FILE))
	 -diff <(./s21_cat --number $(FILE)) <(cat --number $(FILE))
	 -diff <(./s21_cat -b $(FILE)) <(cat -b $(FILE))
	 -diff <(./s21_cat --number-nonblank $(FILE)) <(cat --number-nonblank $(FILE))
	 -diff <(./s21_cat -etsnb $(FILE)) <(cat -etsnb $(FILE))

	$(CHECK) ./s21_cat $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -e $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -t $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -s $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -n $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -b $(FILE) | grep ERROR
	$(CHECK) ./s21_cat -etsnb $(FILE) | grep ERROR
	
	
.PHONY: tests