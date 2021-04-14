CC = gcc
OBJ = main.o demonlib.o
$(OBJ): demonlib.h
all: main.o demonlib.o 
	$(CC) -o Demon.out $(OBJ)
	make clean 

main.o: main.c
	$(CC) -c -o main.o main.c

demonlib.o: demonlib.c
	$(CC) -c -o demonlib.o demonlib.c

test: test.c demonlib.c
	$(CC) -o test.out test.c demonlib.c
	make clean
clean: 
	rm -rvf *.o 