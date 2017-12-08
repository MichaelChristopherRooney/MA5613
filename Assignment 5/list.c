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

List insert_after(const char *find, const char *word, List l){
	if(l.head == NULL){
		return l;
	}
	Cell *found_cell = find_cell_with_word(find, l);
	Cell *new_cell = create_cell_with_word(word);
	if(l.tail == found_cell){
		l.tail = new_cell;
	}
	new_cell->prev = found_cell;
	if(found_cell->next != NULL){
		new_cell->next = found_cell->next;
		found_cell->next->prev = new_cell;
		found_cell->next = new_cell;
	} else {
		found_cell->next = new_cell;
	}
	return l;
}

List insert_before(const char *find, const char *word, List l){
	if(l.head == NULL){
		return l;
	}
	Cell *found_cell = find_cell_with_word(find, l);
	Cell *new_cell = create_cell_with_word(word);
	if(l.head == found_cell){
		l.head = new_cell;
	}
	new_cell->next = found_cell;
	if(found_cell->prev != NULL){
		new_cell->prev = found_cell->prev;
		found_cell->prev->next = new_cell;
		found_cell->prev = new_cell;
	} else {
		found_cell->prev = new_cell;
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

// Prints list in reverse to verify that prev has been set correctly.
void print_list_reverse(const List l){
	printf("*** Printing list in reverse ***\n");
	if(l.tail == NULL){
		printf("List is empty.\n");
	}
	Cell *c = l.tail;
	int i = 0;
	do {
		printf("Cell %d contains: %s\n", i, c->word);
		c = c->prev;
		i++;
	} while(c != NULL);	
}

void print_list(const List l){
	printf("*** Printing list ***\n");
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

// Reverse the list by traversing it and swapping the prev and next pointers in each cell.
// Finally it then swaps the head and tail cells.
List reverse(List l){
	if(l.head == NULL){
		return l;
	}
	Cell *c = l.head;
	Cell *temp;
	do {
		if(c->prev == NULL){ // is old head
			temp = c->next;
			c->next = NULL;
			c->prev = temp;
			c = temp;
		} else if(c->next == NULL){ // is old tail
			c->next = c->prev;
			c->prev = NULL;
			c = NULL;
		} else { // is non-head/tail cell
			temp = c->next;
			c->next = c->prev;
			c->prev = temp;
			c = temp;
		}
	} while(c != NULL);
	temp = l.head;
	l.head = l.tail;
	l.tail = temp;
	return l;
}

void free_list(List l){
	Cell *c = l.head;
	while(c != NULL){
		Cell *next = c->next;
		free(c);
		c = next;		
	}
}
