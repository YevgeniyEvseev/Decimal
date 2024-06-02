CC=gcc -g

CFLAG= -Wall -Wextra -Werror 

FILE=bcd.c decimal_main.c mantissa.c

CHECK=-lcheck -lsubunit -lrt -lpthread 

all: main exc

main: decimal
	$(CC) *.o test.c -g -o test_main -lm

decimal:
	$(CC) $(CFLAG) -c $(FILE) -lm

exc:
	./test_main

check_test:
	$(CC)  $(FILE)  check.c -o test -lm $(CHECK)