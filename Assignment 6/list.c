#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Helper function used in find_before and find_after
static Cell * find_cell_with_word(const char *word, const List l){
	Cell *c = l.head;
	if(c == NULL){
		printf("Warning: list is empty.\n");
		return NULL;
	}
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

// Helper function that strips newline character before inserting word
static Cell * create_cell_with_word_with_newline(const char *word){
	int wlen = strlen(word); // EXCLUDES \0 byte
	Cell *c = calloc(1, sizeof(Cell));
	c->word = malloc(wlen);	
	memcpy(c->word, word, wlen);
	return c;
}


// Takes a line from the input file and splits it into tokens based on spaces and newlines.
// Example: "one two three\n" will be split into "one", "two" and "three".
// If strtok returns NULL on the first call it means the line is empty.
// Returns 1 if empty line, else 0
static int set_cells_from_string(char *str, Cell **first, Cell **last){
	char *tok = strtok(str, " \n");
	if(tok == NULL){
		return 1;
	}
	Cell *c = create_cell_with_word_with_newline(tok);
	*first = c;
	*last = c;
	while((tok = strtok(NULL, " \n")) != NULL){
		Cell *temp = create_cell_with_word_with_newline(tok);
		c->next = temp;
		temp->prev = c;
		c = temp;
	}
	*last = c;
	return 0;
}

List read_textfile(char *filename){
	size_t size = 256;
	List l = {.head=NULL, .tail=NULL};
	FILE *fp = fopen(filename, "r");
	char *buffer = malloc(sizeof(char) * size);
	if(!fp){
		printf("Warning: %s does not exist.\n", filename);
		return l;
	}
	if(feof(fp)){
		printf("Warning: %s is empty.\n", filename);
		return l;
	}
	// Do first line to set the head
	Cell *first, *last, *prev;
	getline(&buffer, &size, fp);
	set_cells_from_string(buffer, &first, &last);
	l.head = first;
	prev = last;
	while(1){
		getline(&buffer, &size, fp);
		if(feof(fp)){
			break;
		}
		int result = set_cells_from_string(buffer, &first, &last);
		if(result == 0){
			prev->next = first;
			first->prev = prev;
			prev = last;
		}
	}
	l.tail = prev;
	return l;
}

List insert_after(char *find, char *word, List l){
	Cell *found_cell = find_cell_with_word(find, l);
	if(found_cell == NULL){
		printf("Warning: %s was not found in the list, not inserting %s\n", find, word);
		return l;
	}
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

List insert_before(char *find, char *word, List l){
	Cell *found_cell = find_cell_with_word(find, l);
	if(found_cell == NULL){
		printf("Warning: %s was not found in the list, not inserting %s\n", find, word);
		return l;
	}
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

List append(char *word, List l){
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
void print_list_reverse(List l){
	printf("*** Printing list in reverse ***\n");
	if(l.tail == NULL){
		printf("List is empty.\n");
		return;
	}
	Cell *c = l.tail;
	int i = 0;
	do {
		printf("Cell %d contains: %s\n", i, c->word);
		c = c->prev;
		i++;
	} while(c != NULL);	
}

void print_list(List l){
	printf("*** Printing list ***\n");
	if(l.head == NULL){
		printf("List is empty.\n");
		return;
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
	Cell *c = l.head;
	Cell *temp;
	while(c != NULL){
		temp = c->next;
		c->next = c->prev;
		c->prev = temp;
		c = temp;
	}
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

