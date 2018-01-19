#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/////////////////////////////////////////////////////////////////////////////
// List
/////////////////////////////////////////////////////////////////////////////

struct list_entry {
	void *data;
	struct list_entry *next;
	struct list_entry *prev;
};

struct list {
	struct list_entry *head;
	struct list_entry *tail;
};

void append_entry_to_list(struct list *l, void *data);
void remove_entry_from_list(struct list *l, struct list_entry *e);
void remove_entry_from_list_by_data(struct list *l, void *data);

/////////////////////////////////////////////////////////////////////////////
// General vertex stuff
/////////////////////////////////////////////////////////////////////////////

struct vertex_cell * get_vertex_by_id(int id);
struct vertex_cell *get_connection_by_index(struct vertex_cell *v, int i);

// This stores the vertex number (id) and all connected vertices.
// The connections field will points to entries in the ALL_VERTICES array.
// The connections array will default to CONNECTIONS_ARRAY_START_SIZE elements.
// If more space is needed realloc() will be used to grow the array.
struct vertex_cell {
	int number;
	struct list *connections;
	//struct vertex_cell **connections;
	int num_connections;
	int connection_array_size;
	struct subgraph *subgraph_link;
};

struct list *ALL_VERTICES;
int NUM_VERTICES;

int read_vertices_from_file(char *filename);

/////////////////////////////////////////////////////////////////////////////
// Subgraph
/////////////////////////////////////////////////////////////////////////////

// connections_visited is used to prevent inifite loops by recording
// that we have already visited this entry's connections.
struct subgraph_entry {
	struct vertex_cell *vertex;
	int connections_visited;
};

struct subgraph {
	struct list *entries;
	int num_vertices;
	int id;
};

struct list *subgraphs;

int NUM_SUBGRAPHS;

void find_subgraphs();
void find_distances_for_all_subgraphs();

/////////////////////////////////////////////////////////////////////////////
// Distance / histogram
/////////////////////////////////////////////////////////////////////////////

void print_distance_histograms();



