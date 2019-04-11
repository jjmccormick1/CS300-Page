CC=clang
CXX=clang++
CFLAGS=-ggdb -Wall
.DEFAULT_GOAL := all
.PHONY: gen all test

procgen:
	@$(CC) $(CFLAGS) -D PROCGEN procgen.c -o procgen


sched: proc
	@$(CC) $(CFLAGS) -c procgen.c
	@$(CC) $(CFLAGS) -c sched.c
	@$(CC) $(CFLAGS) procgen.o proc.o sched.o -o sched -lm

proc:
	@$(CC) $(CFLAGS) -c proc.c

proctest:
	@$(CC) $(CFLAGS) -D TEST proc.c -o proctest
	@./proctest

all: procgen sched

run: sched
	@./sched

clean:
	@rm -f sched
	@rm -f procgen
	@rm -f proctest
	@rm -f *.proc
	@rm -f *.o
