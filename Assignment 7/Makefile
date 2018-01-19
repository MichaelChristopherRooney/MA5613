OBJECTS = main.o vertex_loader.o subgraph.o distance_finder.o list.o
CC = gcc
CFLAGS = -Wall -g
EXEC_NAME = prog

all: main.o vertex_loader.o subgraph.o distance_finder.o list.o
	$(CC) -o $(EXEC_NAME) main.o vertex_loader.o subgraph.o distance_finder.o list.o $(CFLAGS)

main.o: main.c common.h
	$(CC) -c main.c $(CFLAGS)

vertex_loader.o: vertex_loader.c common.h
	$(CC) -c vertex_loader.c $(CFLAGS)

subgraph.o: subgraph.c common.h
	$(CC) -c subgraph.c $(CFLAGS)

distance_finder.o: distance_finder.c common.h
	$(CC) -c distance_finder.c $(CFLAGS)

list.o: list.c list.h
	$(CC) -c list.c $(CFLAGS)

clean:
	rm -f $(OBJECTS) $(EXEC_NAME)

