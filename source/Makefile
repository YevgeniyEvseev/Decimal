CC=gcc #-Wall -Werror -Wextra

all: clean main.o bcd.o another.o
	$(CC) -o Decimal main.o bcd.o another.o

debug:
	$(CC) -o Decimal main.c source/bcd.c source/another.c -g

main.o: main.c 
	$(CC) -c main.c

bcd.o: source/bcd.c 
	$(CC) -c source/bcd.c 

another.o: source/another.c 
	$(CC) -c source/another.c

clean:
	rm -rf *.o Decimal 