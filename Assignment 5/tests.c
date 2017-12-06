#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "tests.h"

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

// Tests the append function going forward in the list
const static int test_append_forward(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "one", "two", "three" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests the append function going backward in the list
const static int test_append_backward(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "three", "two", "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), BACKWARD);
}

// Tests reversing a list that contains multiple pieces of data.
const static int test_reverse_list_many(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "three", "two", "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	l = reverse(l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests reversing a list that contains two pieces of data.
const static int test_reverse_list_double(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "two", "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = reverse(l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests reversing a list that contains two pieces of data.
const static int test_reverse_list_single(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = reverse(l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// An array of function pointers that contains the test functions.
const static int (*TEST_FUNCS[]) (void) = { test_append_forward, test_append_backward, test_reverse_list_many, test_reverse_list_double, test_reverse_list_single };

void run_all_tests(){
	int num_tests = sizeof(TEST_FUNCS) / sizeof(*TEST_FUNCS);
	int i;
	for(i = 0; i < num_tests; i++){
		int result = (*TEST_FUNCS[i])();
		if(result == 1){
			printf("*** Test failed. ***\n");
		} else {
			printf("Test passed.\n");
		}
		
	}
}
