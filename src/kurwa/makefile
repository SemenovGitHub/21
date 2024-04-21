CC = gcc

CFLAGS = -Wall -Werror -Wextra

EX = ../build/

all : main

main : graph.o polska_parcer.o polska_math.o
	$(CC) $(CFLAGS) $^ -o $@

graph : graph.o polska_parcer.o polska_math.o
	$(CC) $(CFLAGS) $^ -o $(EX)graph

graph.o : graph.c polska_parcer.h
	$(CC) $(CFLAGS) -c $< -o $@

polska_parcer.o : polska_parcer.c polska_parcer.h
	$(CC) $(CFLAGS) -c $< -o $@

polska_math.o : polska_math.c polska_math.h
	$(CC) $(CFLAGS) -c $< -o $@
	
clean :
	rm -f *.o main rm -f $(EX)graph
    
rebuild : clean all
