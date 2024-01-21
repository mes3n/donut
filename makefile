# Variables to control Makefile operation

CC = gcc
CCFLAGS = -Wall -g -lm
IN = main.c
OUT = donut

main: $(IN)
	$(CC) $(CCFLAGS) -o $(OUT) $^

