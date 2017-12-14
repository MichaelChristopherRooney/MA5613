objects = main.o list.o
CC = gcc
CFLAGS = -Wall
EXEC_NAME = prog

all: main.o list.o
	$(CC) -o $(EXEC_NAME) main.o list.o $(CFLAGS)

main.o: main.c list.h
	$(CC) -c main.c $(CFLAGS)

list.o: list.c list.h
	$(CC) -c list.c $(CFLAGS)

clean:
	rm -f $(objects) $(EXEC_NAME)

