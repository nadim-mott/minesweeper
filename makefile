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

minesweeper: minesweeper_cmdline_basic.o minesweeper.o utils.o
	$(CC) $(FLAGS) -o $@ $^ -lm

%.o: %.c minesweeper.h utils.h
	$(CC) $(FLAGS) -c -o $@ $<

.PHONY: clean all debug release
clean:
	rm -f $(TARGETS) *.o
