#
# File Name   : Makefile
# Description : Makefile for the compiler project2
# 
# Course      : Compiler
#

LEX = flex

YACC = bison
YFLAGS = -vd

CC = gcc
CFLAGS = -g
LDFLAGS =

# Modify here if there are additional source files.
OBJECTS = subc.tab.o lex.yy.o

all: subc

subc: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o subc

lex.yy.o: lex.yy.c subc.tab.h

subc.tab.o: subc.tab.c

lex.yy.c: subc.l
	$(LEX) $(LFLAGS) subc.l

subc.tab.h subc.tab.c: subc.y
	$(YACC) $(YFLAGS) subc.y

clean: 
	rm -f *.o *.tab.* lex.yy.c subc
