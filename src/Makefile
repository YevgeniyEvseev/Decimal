CC=gcc 

CFLAG= -Wall -Wextra -Werror 

FILE=bcd.c decimal_main.c mantissa.c

CHECK=-lcheck -lsubunit -lrt -lpthread 

all: main exc

main:
	$(CC) $(FILE) test.c -g -o test_main -lm

exc:
	./test_main

check_test:
	$(CC) $(FILE)  check.c -o test -lm $(CHECK)