#include "common.h"

// Checks if the element at ALL_VERTICES[number] matches the passed number,
// and returns if so as the vertex already exists. This also checks if 
// NUM_VERTICES > 0 otherwise inserting vertex 0 will fail as the array 
// contains 0 initially.
static void insert_new_vertex(int vert_num){
	if(vert_num > VERTEX_ARRAY_CUR_SIZE){
		// TODO: realloc
	}
	if(ALL_VERTICES[vert_num].number == vert_num && NUM_VERTICES > 0){ 
		return;
	}
	ALL_VERTICES[vert_num].number = vert_num;
	ALL_VERTICES[vert_num].num_connections = 0;
	ALL_VERTICES[vert_num].connections = calloc(1, sizeof(struct vertex_cell *) * CONNECTIONS_ARRAY_START_SIZE);
	NUM_VERTICES++;
}

// First of all create the connection vertex if it does not exist already.
static void insert_new_connection(int vert_num, int conn_num){
	insert_new_vertex(conn_num);
	struct vertex_cell *v = &(ALL_VERTICES[vert_num]);
	if(v->connection_array_size == v->num_connections){
		// TODO: realloc();
	}
	v->connections[v->num_connections] = &(ALL_VERTICES[conn_num]);
	v->num_connections++;	
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
	int vert_num = atoi(tok);
	insert_new_vertex(vert_num);
	while((tok = strtok(NULL, ";\n")) != NULL){
		insert_new_connection(vert_num, atoi(tok));
	}
}

int read_vertices_from_file(char *filename){
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
