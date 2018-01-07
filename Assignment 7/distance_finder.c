#include "common.h"

struct histogram_entry {
	int distance;
	int num_vertices;
	struct histogram_entry *next;
};

struct histogram_list {
	struct histogram_entry *head;
	struct histogram_entry *tail;
};

struct visited_vertex {
	struct vertex_cell *vertex;
	struct visited_vertex *prev;
	struct visited_vertex *next;
};

struct visited_vertex_list {
	struct visited_vertex *head;
	struct visited_vertex *tail;
};

// TODO: rename
static struct visited_vertex *was_vertex_already_visited(struct visited_vertex_list *visited, struct vertex_cell *v){
	struct visited_vertex *cur = visited->head;
	while(cur != NULL){
		if(cur->vertex->number == v->number){
			return cur;
		}
		cur = cur->next;
	}
	return NULL;
}

static void add_visited_vertex(struct visited_vertex_list *vl, struct vertex_cell *v){
	if(vl->head == NULL){
		vl->head = calloc(1, sizeof(struct visited_vertex));
		vl->tail = vl->head;
		vl->head->vertex = v;
	} else {
		vl->tail->next = calloc(1, sizeof(struct visited_vertex));
		vl->tail->next->prev = vl->tail;
		vl->tail = vl->tail->next;
		vl->tail->vertex = v;
	}
}

static void remove_visited_vertex(struct visited_vertex_list *vl, struct vertex_cell *v){
	struct visited_vertex *cur = was_vertex_already_visited(vl, v);
	if(cur == vl->head){
		vl->head = NULL;
		vl->tail = NULL;
	} else if(cur == vl->tail){
		vl->tail = cur->prev;
		vl->tail->next = NULL;
	} else {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
	}
	free(cur);
}

// First of all checks if the vertices are adjacent.
// If not it then...
// TODO: comment
// TODO: cleanup
static int find_distance_between_vertices(struct subgraph *s, struct vertex_cell *v1, struct vertex_cell *v2, int depth, struct visited_vertex_list *visited, int shortest_distance){
	add_visited_vertex(visited, v1);
	int i;
	for(i = 0; i < v1->num_connections; i++){
		if(v1->connections[i]->number == v2->number){
			remove_visited_vertex(visited, v1);
			return depth + 1;
		}
		struct vertex_cell *v_conn = v1->connections[i];
		if(was_vertex_already_visited(visited, v_conn) == NULL){
			int distance = find_distance_between_vertices(s, v_conn, v2, depth + 1, visited, shortest_distance);
			if(distance != 0){
				if(distance < shortest_distance || shortest_distance == 0){
					shortest_distance = distance;
				}
			}
		}
	}
	remove_visited_vertex(visited, v1);
	return shortest_distance;
}

static struct histogram_entry *find_distance_in_histogram(struct histogram_list *hl, int distance){
	struct histogram_entry *e = hl->head;
	while(e != NULL){
		if(e->distance == distance){
			return e;
		}
		e = e->next;
	}
	return NULL;
}

static struct histogram_entry *add_entry_to_histogram(struct histogram_list *hl, int distance){
	struct histogram_entry *e = calloc(1, sizeof(struct histogram_entry));
	e->distance = distance;
	if(hl->head == NULL){
		hl->head = e;
		hl->tail = e;
	} else {
		hl->tail->next = e;
		hl->tail = e;
	}
	return e;
}

static void store_distance_in_histogram(struct subgraph *s, struct histogram_list *hl, int distance){
	struct histogram_entry *e = find_distance_in_histogram(hl, distance);
	if(e == NULL){
		e = add_entry_to_histogram(hl, distance);
	}
	e->num_vertices++;
}

static void print_histogram(struct histogram_list *hl){
	printf("Distance\tNumber of node pairs\n");
	struct histogram_entry *e = hl->head;
	while(e != NULL){
		printf("%d\t\t%d\n", e->distance, e->num_vertices);
		e = e->next;
	}
}

static void find_distance_between_subgraph_vertices(struct subgraph *s){
	struct histogram_list *hl = calloc(1, sizeof(struct histogram_list));
	struct subgraph_entry *e1 = s->head;
	struct subgraph_entry *e2 = s->head->next;
	if(e2 == NULL){
		printf("Only one entry - cannot calculate any distances\n");
		return;
	}
	while(e1 != NULL){
		while(e2 != NULL){
			struct visited_vertex_list *visited = calloc(1, sizeof(struct visited_vertex));
			int distance = find_distance_between_vertices(s, e1->vertex, e2->vertex, 0, visited, 0);
			store_distance_in_histogram(s, hl, distance);
			e2 = e2->next;
		}
		e1 = e1->next;
		if(e1 != NULL){
			e2 = e1->next;
		}
	}
	print_histogram(hl);
}

void print_distance_histograms(){
	int i = 0;
	struct subgraph *cur = subgraphs;
	while(cur != NULL){
		printf("Subgraph %d:\n", i);
		find_distance_between_subgraph_vertices(cur);
		cur = cur->next;
		i++;
	}	
}
