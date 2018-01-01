#include "common.h"

// connections_visited is used to prevent inifite loops by recording
// that we have already visited this entry's connections.
struct subgraph_entry {
	struct vertex_cell *vertex;
	int connections_visited;
	struct subgraph_entry *next;
};

struct subgraph {
	struct subgraph_entry *head;
	struct subgraph_entry *tail;
	struct subgraph *next;
	int num_vertices;	
};

struct subgraph *subgraphs;

int NUM_SUBGRAPHS = 0;

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

static void print_subgraphs(){
	struct subgraph *s = subgraphs;
	while(s != NULL){
		printf("Subgraph contains %d vertices: ", s->num_vertices);
		struct subgraph_entry *e = s->head;
		while(e != NULL){
			printf("%d, ", e->vertex->number);
			e = e->next;
		}
		printf("\n");
		s = s->next;
	}
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
	//printf("Looking at %d and %d\n", v1->number, v2->number);	
	add_visited_vertex(visited, v1);
	//printf("Added %d to visited list.\n", v1->number);
	int i;
	for(i = 0; i < v1->num_connections; i++){
		if(v1->connections[i]->number == v2->number){
			remove_visited_vertex(visited, v1);
			return depth + 1;
		}
		struct vertex_cell *v_conn = v1->connections[i];
		if(was_vertex_already_visited(visited, v_conn) == NULL){
			//printf("Have not visited %d\n", v_conn->number);
			printf("Currently at %d, going to %d\n", v1->number, v_conn->number);	
			int distance = find_distance_between_vertices(s, v_conn, v2, depth + 1, visited, shortest_distance);
			if(distance != 0){
				if(distance < shortest_distance || shortest_distance == 0){
					shortest_distance = distance;
				}
			}
		} else {
			//printf("Already visited %d\n", v_conn->number);
		}
	}
	//printf("Removed %d from visited list.\n", v1->number);
	remove_visited_vertex(visited, v1);
	return shortest_distance;
}

static void find_distance_between_subgraph_vertices(struct subgraph *s){
	int i, j;
	for(i = 0; i < s->num_vertices; i++){
		for(j = i + 1; j < s->num_vertices; j++){
			if(i != 0 || j != 6){
				continue;
			}
			struct subgraph_entry *e1 = get_subgraph_entry_for_vertex(s, i);
			struct subgraph_entry *e2 = get_subgraph_entry_for_vertex(s, j);
			struct visited_vertex_list *visited = calloc(1, sizeof(struct visited_vertex));
			printf("Distance between %d and %d\n", i, j);
			int distance = find_distance_between_vertices(s, e1->vertex, e2->vertex, 0, visited, 0);
			printf("Distance between %d and %d is %d\n", i, j, distance);
		}	
	}
}

// Note: the first vertex is handled outside of the for loop, so the for loop
// starts at i=1.
void find_subgraphs(){
	subgraphs = calloc(1, sizeof(struct subgraph));
	struct subgraph *cur = subgraphs;
	struct subgraph *next;
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
		find_subgraph_from_starting_vertex(cur, &(ALL_VERTICES[i]));
		NUM_SUBGRAPHS++;
	}
	print_subgraphs();
	printf("Number of subgraphs: %d\n", NUM_SUBGRAPHS);
	find_distance_between_subgraph_vertices(subgraphs);
}
