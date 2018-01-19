#include "common.h"

struct histogram_entry {
	int distance;
	int num_vertices;
};

static struct vertex_cell *find_vertex_in_list(struct list *visited, struct vertex_cell *v){
	struct list_entry *cur = visited->head;
	while(cur != NULL){
		struct vertex_cell *c = cur->data;
		if(c->number == v->number){
			return c;
		}
		cur = cur->next;
	}
	return NULL;
}

// This function is recursive.
// It finds the shortest path from v1 to v2 by following v1's connections.
// Shortest distance will be set to zero on the first call.
// A list of visited vertices is kept to avoid infinite loops and redundant checking.
static int find_distance_between_vertices(struct subgraph *s, struct vertex_cell *v1, struct vertex_cell *v2, int depth, struct list *visited, int shortest_distance){
	append_entry_to_list(visited, v1);
	int i;
	for(i = 0; i < v1->num_connections; i++){
		struct vertex_cell *v_conn = get_connection_by_index(v1, i);
		if(v_conn->number == v2->number){
			remove_entry_from_list_by_data(visited, v1);
			return depth + 1;
		}
		if(find_vertex_in_list(visited, v_conn) == NULL){
			int distance = find_distance_between_vertices(s, v_conn, v2, depth + 1, visited, shortest_distance);
			if(distance != 0){
				if(distance < shortest_distance || shortest_distance == 0){
					shortest_distance = distance;
				}
			}
		}
	}
	remove_entry_from_list_by_data(visited, v1);
	return shortest_distance;
}

static struct histogram_entry *find_distance_in_histogram(struct list *hl, int distance){
	struct list_entry *e = hl->head;
	while(e != NULL){
		struct histogram_entry *he = e->data;
		if(he->distance == distance){
			return he;
		}
		e = e->next;
	}
	return NULL;
}

static struct histogram_entry *add_entry_to_histogram(struct list *hl, int distance){
	struct histogram_entry *e = calloc(1, sizeof(struct histogram_entry));
	e->distance = distance;
	append_entry_to_list(hl, e);
	return e;
}

static void store_distance_in_histogram(struct subgraph *s, struct list *hl, int distance){
	struct histogram_entry *e = find_distance_in_histogram(hl, distance);
	if(e == NULL){
		e = add_entry_to_histogram(hl, distance);
	}
	e->num_vertices++;
}

static void print_histogram(struct list *hl){
	printf("Distance\tNumber of node pairs\n");
	struct list_entry *e = hl->head;
	while(e != NULL){
		struct histogram_entry *he = e->data;
		printf("%d\t\t%d\n", he->distance, he->num_vertices);
		e = e->next;
	}
}

static void find_distance_between_subgraph_vertices(struct subgraph *s){
	struct list *hist_list = calloc(1, sizeof(struct list));
	struct list_entry *l1 = s->entries->head;
	struct list_entry *l2 = s->entries->head->next;
	if(l2 == NULL){
		printf("Only one entry - cannot calculate any distances\n");
		return;
	}
	while(l1 != NULL){
		while(l2 != NULL){
			struct subgraph_entry *e1 = l1->data;
			struct subgraph_entry *e2 = l2->data;
			struct list *visited = calloc(1, sizeof(struct list));
			int distance = find_distance_between_vertices(s, e1->vertex, e2->vertex, 0, visited, 0);
			store_distance_in_histogram(s, hist_list, distance);
			l2 = l2->next;
		}
		l1 = l1->next;
		if(l1 != NULL){
			l2 = l1->next;
		}
	}
	print_histogram(hist_list);
}

void print_distance_histograms(){
	int i = 0;
	struct list_entry *l = subgraphs->head;
	while(l != NULL){
		printf("Subgraph %d:\n", i);
		find_distance_between_subgraph_vertices(l->data);
		l = l->next;
		i++;
	}	
}
