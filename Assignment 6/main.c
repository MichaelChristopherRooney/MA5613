#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

enum direction { FORWARD, BACKWARD };

// Helper function for tests.
// Takes an already filled list and the words expected to be in it.
// Checks if the list contains the expected words, and if the list is the right size.
static int compare_expected_and_list(const char *test_name, List l, const char *expected_words[], const int num_expected, const enum direction dir){
	int i;
	Cell *cur;
	if(dir == FORWARD){
		cur = l.head;
	} else {
		cur = l.tail;
	}
	for(i = 0; i < num_expected; i++){
		if(cur == NULL){
			printf("Error in test \"%s\": found end of list while looking for %s\n", test_name, expected_words[i]);
			return 1;
		}
		if(strcmp(expected_words[i], cur->word) != 0){
			printf("Error in test \"%s\": expected \"%s\" but got \"%s\"\n", test_name, expected_words[i], cur->word);
			return 1;
		}
		if(dir == FORWARD){
			cur = cur->next;
		} else {
			cur = cur->prev;
		}
	}
	if(cur != NULL){
		printf("Error in test \"%s\": list has more elements than expected.\n", test_name);
		return 1;
	}
	return 0;
}

// Writes to a binary file then reads the data back in.
// Checks that all expected words are present and in the correct location.
// Checks that both next and prev have been set properly
static void test_binary_file(char *filename){
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	write_binfile(l, filename);
	l = read_binfile(filename);
	// First check that the prev field has been set correctly.
	const char *expected_forward[] = { "one", "two", "three" };
	int result = compare_expected_and_list("Binary file", l, expected_forward, 3, FORWARD);
	if(result == 1){
		printf("Binary file test failed using forward traversal!\n");
	} else {
		printf("Binary file test passed using forward traversal!\n");
	}
	// Now check that the prev field has been set correctly.
	const char *expected_backward[] = { "three", "two", "one",};
	result = compare_expected_and_list("Binary file", l, expected_backward, 3, BACKWARD);
	if(result == 1){
		printf("Binary file test failed using backward traversal!\n");
	} else {
		printf("Binary file test passed using backward traversal!\n");
	}
}

static void test_text_file(char *filename){
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	write_textfile(l, filename);
	l = read_textfile(filename);
	// First check that the prev field has been set correctly.
	const char *expected_forward[] = { "one", "two", "three" };
	int result = compare_expected_and_list("Text file", l, expected_forward, 3, FORWARD);
	if(result == 1){
		printf("Text file test failed using forward traversal!\n");
	} else {
		printf("Text file test passed using forward traversal!\n");
	}
	// Now check that the prev field has been set correctly.
	const char *expected_backward[] = { "three", "two", "one",};
	result = compare_expected_and_list("Text file", l, expected_backward, 3, BACKWARD);
	if(result == 1){
		printf("Text file test failed using backward traversal!\n");
	} else {
		printf("Text file test passed using backward traversal!\n");
	}
}

int main(void){
	// NOTE: if changing the tests make sure you update the expected word arrays for BOTH directions.
	// Ex: use { "one", "two" } when traversing forward, and { "two", "one" } when traversing backward.
	test_binary_file("hi.bin");
	test_text_file("hi.txt");
	return 0;
}

