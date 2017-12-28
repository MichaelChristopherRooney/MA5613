#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct connection_cell {
	int number;
	struct connection_cell *next;
};

struct vertex {
	int number;
	struct connection_cell *connections;
};

static void print_vertex_connections(struct vertex *v){
	if(v->connections == NULL){
		printf("Vertex %d has no connections.\n", v->number);
		return;
	}
	printf("Vertex %d is connected to: ", v->number);
	struct connection_cell *c = v->connections;
	while(c != NULL){
		if(c->next == NULL){
			printf("%d.\n", c->number);			
		} else {
			printf("%d, ", c->number);
		}
		c = c->next;
	}
	return;
}

// Takes a line from the input file, tokenises it and then creates vertices from it.
// Example: "0;1;2\n" is split into "0", "1", "2", which is taken to be mean that 
// vertex 0 is connected to vertices 1 and 2.
// Tokens are ';' and '\n'
static void parse_vertex_from_line(char *line){
	char *tok = strtok(line, ";\n");
	if(tok == NULL){
		printf("Warning: line contains no data after tokenisation - ignoring it.\n");
		return;
	}
	struct vertex v; // TODO: store this somewhere outside of this function
	v.number = atoi(tok);
	struct connection_cell *prev = NULL;
	struct connection_cell *cur = NULL;
	int is_first = 1;
	while((tok = strtok(NULL, ";\n")) != NULL){
		if(is_first){
			is_first = 0;
			v.connections = malloc(sizeof(struct connection_cell));
			v.connections->number = atoi(tok);
			prev = v.connections;
		} else {
			cur = malloc(sizeof(struct connection_cell));
			cur->number = atoi(tok);
			prev->next = cur;
			prev = cur;
		}
	}
	print_vertex_connections(&v);
}

static int read_vertices_from_file(char *filename){
	FILE *fp = fopen(filename, "r");
	if(!fp){
		printf("Error: cannot open file: %s\n", filename);
		return 1;
	}
	size_t size = 256;
	char *buffer = malloc(sizeof(char) * size);
	while(1){
		getline(&buffer, &size, fp);
		if(feof(fp)){
			break;
		}
		parse_vertex_from_line(buffer);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: expected filename passed as arg!\n");
		return 1;
	}
	char *filename = argv[1];
	printf("Filename is: %s\n", filename);
	if(read_vertices_from_file(filename) == 1){
		return 1;
	}	
	return 0;
}
