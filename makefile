##
# Minesweeper - A simple minesweeper game
# 			By Nadim A. Mottu
##

CC := gcc
FLAGS := -Wall --std=gnu99
PORT := port.mk 
TARGETS := minesweeper

debug: FLAGS += -ggdb3 -DDEBUG
debug: all

release: FLAGS += -O2 
release: all

all: $(TARGETS)

minesweeper: minesweeper_cmdline_basic.o minesweeper.o utils.o solver.o AC3.o
	$(CC) $(FLAGS) -o $@ $^ -lm

minesweeper_cmdline_basic.o: minesweeper_cmdline_basic.c minesweeper.h solver.h
	$(CC) $(FLAGS) -c -o $@ $<

minesweeper.o : minesweeper.c minesweeper.h utils.h
	$(CC) $(FLAGS) -c -o $@ $<

utils.o : utils.c utils.h
	$(CC) $(FLAGS) -c -o $@ $<

AC3.o : AC3.c AC3.h
	$(CC) $(FLAGS) -c -o $@ $<

solver.o : solver.c solver.h AC3.h
	$(CC) $(FLAGS) -c -o $@ $<



.PHONY: clean all debug release
clean:
	rm -f $(TARGETS) *.o
