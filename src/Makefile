CC=gcc -g

CFLAG= -Wall -Wextra -Werror 

FILE=bcd.c decimal_main.c mantissa.c

CHECK=-lcheck -lsubunit -lrt -lpthread 

all: main exc

main: decimal
	$(CC) ./object_file/*.o test.c -g -o test_main -lm

decimal:
	mkdir object_file
	$(CC) $(CFLAG) -c $(FILE) -lm
	mv *.o ./object_file

exc:
	./test_main

check_test: decimal 
	$(CC)  ./object_file/*.o check.c -o test -lm $(CHECK)

clean:
	rm -rf *.o
	rm -rf object_file
	rm -f ./test
	rm -f ./test_main