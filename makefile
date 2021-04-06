CC = gcc
all: main.o demonlib.o
	echo "Making executable file"
	$(CC) -o Demon.out main.o demon.o

main.o: main.c
	echo "Making main.o"
	$(CC) -c -o main.o main.c

demonlib.o: demonlib.c
	echo "Making demonlib.o"
	$(CC) -c -o demonlib.0 demonlib.c

clean: 
	echo "Cleaning *.o files"
	rm -rvf *.o 