#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Helper function used in find_before and find_after
static Cell * find_cell_with_word(const char *word, const List l){
	Cell *c = l.head;
	do {
		if(strcmp(c->word, word) == 0){
			return c;
		}
		c = c->next;
	} while(c != NULL);
	return NULL;
}

// Helper function to create a new cell and set its word.
static Cell * create_cell_with_word(const char *word){
	int wlen = strlen(word) + 1; // includes \0 byte
	Cell *c = calloc(1, sizeof(Cell));
	c->word = malloc(wlen);	
	memcpy(c->word, word, wlen);
	return c;
}

// TODO: empty list, other situations like that
List insert_before(const char *find, const char *word, List l){
	Cell *found_cell = find_cell_with_word(find, l);
	Cell *new_cell = create_cell_with_word(word);
	if(l.head == found_cell){
		l.head = new_cell;
	}
	if(l.tail == found_cell){
		l.tail = new_cell;
	}
	new_cell->next = found_cell;
	if(found_cell->prev != NULL){
		new_cell->prev = found_cell->prev;
		found_cell->prev->next = new_cell;
	}
	return l;
}

List append(const char *word, List l){
	if(l.head == NULL){
		Cell *c = create_cell_with_word(word);
		l.head = c;
		l.tail = c;
		return l;
	}
	Cell *c = create_cell_with_word(word);
	c->prev = l.tail;
	l.tail->next = c;
	l.tail = c;
	return l;
}

void print_list(const List l){
	if(l.head == NULL){
		printf("List is empty.\n");
	}
	Cell *c = l.head;
	int i = 0;
	do {
		printf("Cell %d contains: %s\n", i, c->word);
		c = c->next;
		i++;
	} while(c != NULL);	
}

// TODO
void free_list(List l){

}
