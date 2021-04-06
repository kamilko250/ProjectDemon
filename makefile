CC = gcc
OBJ = main.o demonlib.o
$(OBJ): demonlib.h
all: main.o demonlib.o
	@echo "Making executable file"
	$(CC) -o Demon.out $(OBJ) 

main.o: main.c
	@echo "Making main.o"
	$(CC) -c -o main.o main.c

demonlib.o: demonlib.c
	@echo "Making demonlib.o"
	$(CC) -c -o demonlib.o demonlib.c

clean: 
	@echo "Cleaning *.o files"
	rm -rvf *.o 