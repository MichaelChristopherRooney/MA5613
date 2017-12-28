OBJECTS = main.o
CC = gcc
CFLAGS = -Wall
EXEC_NAME = prog

all: main.o
	$(CC) -o $(EXEC_NAME) main.o $(CFLAGS)

main.o: main.c 
	$(CC) -c main.c $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

