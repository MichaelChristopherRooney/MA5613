#include "common.h"

static struct subgraph_entry *get_subgraph_entry_for_vertex(struct subgraph *s, int vert_number){
	struct subgraph_entry *e = s->head;
	while(e != NULL){
		if(e->vertex->number == vert_number){
			return e;
		}
		e = e->next;
	}
	return NULL;
}

static struct subgraph_entry *insert_vertex_into_subgraph(struct subgraph *s, struct vertex_cell *v){
	if(s->head == NULL){ // v will be first entry
		s->head = calloc(1, sizeof(struct subgraph_entry));
		s->tail = s->head;
		s->head->vertex = v;
	} else {
		s->tail->next = calloc(1, sizeof(struct subgraph_entry));
		s->tail = s->tail->next;
		s->tail->vertex = v;
	}
	v->in_subgraph = 1;
	s->num_vertices++;
	return s->tail;
}

// TODO: comment
// Recursively...
static void find_subgraph_from_starting_vertex(struct subgraph *s, struct vertex_cell *v){
	struct subgraph_entry *e = get_subgraph_entry_for_vertex(s, v->number);
	if(e == NULL){
		e = insert_vertex_into_subgraph(s, v);
	}
	e->connections_visited = 1;
	int i;
	for(i = 0; i < v->num_connections; i++){
		struct vertex_cell *v_conn = v->connections[i];
		struct subgraph_entry *e_conn = get_subgraph_entry_for_vertex(s, v_conn->number);
		int conn_visited = 0;
		if(e_conn != NULL){
			conn_visited = e_conn->connections_visited;
		}
		if(conn_visited == 0){
			find_subgraph_from_starting_vertex(s, v_conn);
		}
	}
}

// Note: the first vertex is handled outside of the for loop, so the for loop
// starts at i=1.
void find_subgraphs(){
	NUM_SUBGRAPHS = 0;
	subgraphs = calloc(1, sizeof(struct subgraph));
	struct subgraph *cur = subgraphs;
	struct subgraph *next;
	cur->id = 0;
	find_subgraph_from_starting_vertex(cur, &(ALL_VERTICES[0]));
	NUM_SUBGRAPHS++;
	int i;
	for(i = 1; i < NUM_VERTICES; i++){
		if(ALL_VERTICES[i].in_subgraph == 1){
			continue;
		}
		next = calloc(1, sizeof(struct subgraph));
		cur->next = next;
		cur = next;
		cur->id = 1;
		find_subgraph_from_starting_vertex(cur, &(ALL_VERTICES[i]));
		NUM_SUBGRAPHS++;
	}
	printf("Number of subgraphs: %d\n", NUM_SUBGRAPHS);
}
