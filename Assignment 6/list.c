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
	int wlen = strlen(word) + 1; // includes \0 byte
	Cell *c = calloc(1, sizeof(Cell));
	c->word = malloc(wlen);	
	memcpy(c->word, word, wlen);
	return c;
}


// Takes a line from the input file and splits it into tokens based on spaces and newlines.
// Example: "one two three\n" will be split into "one", "two" and "three".
// If strtok returns NULL on the first call it means the line is empty.
// Returns 0 if line is empty
static int set_cells_from_string(char *line, Cell **first, Cell **last){
	char *tok = strtok(line, " \n");
	if(tok == NULL){
		return 0;
	}
	Cell *c = create_cell_with_word_with_newline(tok);
	*first = c;
	while((tok = strtok(NULL, " \n")) != NULL){
		Cell *temp = create_cell_with_word_with_newline(tok);
		c->next = temp;
		temp->prev = c;
		c = temp;
	}
	*last = c;
	return 1;
}

List read_textfile(char *filename){
	size_t size = 256;
	List l = {.head=NULL, .tail=NULL};
	FILE *fp = fopen(filename, "r");
	char *buffer = malloc(sizeof(char) * size);
	Cell *first, *last, *prev_last;
	int is_first_valid_line = 1;
	if(!fp){
		printf("Warning: %s does not exist.\n", filename);
		return l;
	}
	while(1){
		getline(&buffer, &size, fp);
		if(feof(fp)){
			break;
		}
		if(!set_cells_from_string(buffer, &first, &last)){ // ignore empty lines
			continue;
		}
		if(is_first_valid_line){ // set the head on the first read
			l.head = first;
			prev_last = last;
			is_first_valid_line = 0;
		} else {
			prev_last->next = first;
			first->prev = prev_last;
			prev_last = last;
		}
	}
	l.tail = prev_last;
	fclose(fp);
	return l;
}

List read_binfile(char *filename){
	List l = {.head=NULL, .tail=NULL};
	FILE *fp = fopen(filename, "rb");
	if(!fp){
		printf("Warning: failed to open %s\n", filename);
		return l;
	}
	int total;
	fread(&total, sizeof(int), 1, fp);
	int longest_word;
	fread(&longest_word, sizeof(int), 1, fp);
	char *buf = malloc(sizeof(char) * longest_word);
	int i;
	for(i = 0; i < total; i++){
		int wlen;
		fread(&wlen, sizeof(int), 1, fp);
		fread(buf, sizeof(char), wlen, fp);
		l = append(buf, l);
	}
	free(buf);
	fclose(fp);
	return l;
}

void write_binfile(List l, char *filename){
	FILE *fp = fopen(filename, "wb+");
	if(!fp){
		printf("Warning: failed to create %s\n", filename);
		return;
	}
	// This part of the file will be overwritten once the total and largest word is known.
	int total = 0;
	fwrite(&total, sizeof(int), 1, fp);
	int largest_word = 0;
	fwrite(&total, sizeof(int), 1, fp);
	Cell *c = l.head;
	while(c != NULL){
		total++;
		int wlen = strlen(c->word) + 1; // includes \0 byte
		fwrite(&wlen, sizeof(int), 1, fp);
		fwrite(c->word, 1, wlen, fp);
		if(wlen > largest_word){
			largest_word = wlen;
		}
		c = c->next;
	}
	// Now fill in the total at the start
	rewind(fp);
	fwrite(&total, sizeof(int), 1, fp);
	fwrite(&largest_word, sizeof(int), 1, fp);
	fclose(fp);
	return;
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

