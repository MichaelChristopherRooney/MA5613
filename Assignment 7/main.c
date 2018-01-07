#include "common.h"

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
	if(read_vertices_from_file(filename) == 1){
		return 1;
	}
	find_subgraphs();
	print_distance_histograms();
	return 0;
}
