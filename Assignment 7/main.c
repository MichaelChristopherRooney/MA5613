#include "common.h"

struct vertex_cell *get_connection_by_index(struct vertex_cell *v, int i){
	struct list_entry *e = v->connections->head;
	int n;
	for(n = 0; n < i; n++){
		if(e == NULL){
			return NULL;
		}
		e = e->next;
	}
	return e->data;
}

struct vertex_cell *get_vertex_by_id(int id){
	struct list_entry *e = ALL_VERTICES->head;
	while(e != NULL){
		struct vertex_cell *c = e->data;
		if(c->number == id){
			return c;
		}
		e = e->next;
	}
	return NULL;
}

void init_globals(){
	ALL_VERTICES = calloc(1, sizeof(struct list));
	NUM_VERTICES = 0;
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
