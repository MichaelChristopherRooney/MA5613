#include "common.h"

// First checks if the vertex already exists, as vertices are created when a
// connection a new vertex is found.
static void insert_new_vertex(int vert_num){
	if(get_vertex_by_id(vert_num) != NULL){
		return;
	}
	struct vertex_cell *c = calloc(1, sizeof(struct vertex_cell));
	c->number = vert_num;
	c->num_connections = 0;
	c->connections = calloc(1, sizeof(struct list));	
	append_entry_to_list(ALL_VERTICES, c);
	NUM_VERTICES++;
}

// First of all create the connection vertex if it does not exist already.
static void insert_new_connection(int vert_num, int conn_num){
	insert_new_vertex(conn_num);
	struct vertex_cell *v = get_vertex_by_id(vert_num);
	append_entry_to_list(v->connections, get_vertex_by_id(conn_num));
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

