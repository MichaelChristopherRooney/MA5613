OBJECTS = main.o vertex_loader.o subgraph.o
CC = gcc
CFLAGS = -Wall
EXEC_NAME = prog

all: main.o vertex_loader.o subgraph.o
	$(CC) -o $(EXEC_NAME) main.o vertex_loader.o subgraph.o $(CFLAGS)

main.o: main.c common.h
	$(CC) -c main.c $(CFLAGS)

vertex_loader.o: vertex_loader.c common.h
	$(CC) -c vertex_loader.c $(CFLAGS)

subgraph.o: subgraph.c common.h
	$(CC) -c subgraph.c $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

