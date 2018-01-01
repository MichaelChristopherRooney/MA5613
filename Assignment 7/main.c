#include "common.h"

static void print_vertex_connections(struct vertex_cell *v){
	if(v->connections[0] == NULL){
		printf("Vertex %d has no connections.\n", v->number);
		return;
	}
	printf("Vertex %d is connected to: ", v->number);
	int i;
	for(i = 0; i < v->num_connections; i++){
		printf("%d, ", v->connections[i]->number);
	}
	printf("\n");
}

void init_globals(){
	VERTEX_ARRAY_CUR_SIZE = 0;
	NUM_VERTICES = 0;
	ALL_VERTICES = calloc(1, sizeof(struct vertex_cell) * VERTEX_ARRAY_START_SIZE);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: expected filename passed as arg!\n");
		return 1;
	}
	init_globals();
	char *filename = argv[1];
	printf("Filename is: %s\n", filename);
	if(read_vertices_from_file(filename) == 1){
		return 1;
	}
	int i = 0;
	for(i = 0; i < NUM_VERTICES; i++){
		print_vertex_connections(&(ALL_VERTICES[i]));
	}
	find_subgraphs();
	return 0;
}
