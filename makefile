CC = gcc
all: main.o demonlib.a
	@echo "Making executable file"
	ranlib libholberton.a
	$(CC) -o Demon.out -L. -demonlib main.o 

main.o: main.c
	@echo "Making main.o"
	$(CC) -c -o main.o main.c

demonlib.a: demonlib.o
	@echo "Making demonlib.a"
	ar -rc demonlib.a demonlib.o

demonlib.o: demonlib.c
	@echo "Making demonlib.o"
	$(CC) -c -o demonlib.0 demonlib.c

clean: 
	@echo "Cleaning *.o files"
	rm -rvf *.o 