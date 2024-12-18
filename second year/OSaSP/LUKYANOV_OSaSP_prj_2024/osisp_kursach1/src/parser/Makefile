SHELL:=bash
CC=gcc
CFLAGS=-W -Wall -Wno-unused-parameter -Wno-unused-variable -Werror -std=c11 -O3 -pedantic -c

all: ../../build/parser

../../build/parser: parser.c parser.h Makefile
	$(CC) $(CFLAGS) parser.c -o ../../build/parser