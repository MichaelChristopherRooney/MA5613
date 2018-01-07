#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This stores the vertex number (id) and all connected vertices.
// The connections field will points to entries in the ALL_VERTICES array.
// The connections array will default to CONNECTIONS_ARRAY_START_SIZE elements.
// If more space is needed realloc() will be used to grow the array.
struct vertex_cell {
	int number;
	struct vertex_cell **connections;
	int num_connections;
	int connection_array_size;
	int in_subgraph; // TODO: change to subgraph link
};

#define CONNECTIONS_ARRAY_START_SIZE 32

// An array of all vertices.
// Defaults to VERTEX_ARRAY_START_SIZE number of elements.
// If more space is needed realloc() will be used to grow the array.
struct vertex_cell *ALL_VERTICES;
#define VERTEX_ARRAY_START_SIZE 32
int VERTEX_ARRAY_CUR_SIZE;
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
	struct subgraph_entry *next;
};

struct subgraph {
	struct subgraph_entry *head;
	struct subgraph_entry *tail;
	struct subgraph *next;
	int num_vertices;
	int id;
};

struct subgraph *subgraphs;

int NUM_SUBGRAPHS;

void find_subgraphs();
void find_distances_for_all_subgraphs();

/////////////////////////////////////////////////////////////////////////////
// Distance / histogram
/////////////////////////////////////////////////////////////////////////////

void print_distance_histograms();

