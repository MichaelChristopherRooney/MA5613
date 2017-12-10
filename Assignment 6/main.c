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

// Tests the append function going forward in the list
static int test_append_forward(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "one", "two", "three" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests the append function going backward in the list
static int test_append_backward(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "three", "two", "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = append("three", l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), BACKWARD);
}

// Tests reversing a list that contains multiple pieces of data.
static int test_reverse_list_many(){
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
static int test_reverse_list_double(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "two", "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	l = reverse(l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests reversing a list that contains two pieces of data.
static int test_reverse_list_single(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = reverse(l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests the insert before and insert after functions
static int test_insert_before_and_after_forward(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "one", "two", "three", "four" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	insert_after("one", "four", l);
	insert_before("four", "three", l);
	insert_before("three", "two", l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), FORWARD);
}

// Tests the insert before and insert after functions
static int test_insert_before_and_after_backward(){
	printf("Running test: %s\n", __FUNCTION__);
	const char *expected_words[] = { "four", "three", "two", "one" };
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = insert_after("one", "four", l);
	l = insert_before("four", "three", l);
	l = insert_before("three", "two", l);
	return compare_expected_and_list(__FUNCTION__, l, expected_words, sizeof(expected_words) / sizeof(char *), BACKWARD);
}

// Tests the free function
// Not really anyway to verify this since the free_list specification doesn't
// return anything.
static int test_free(){
	printf("Running test: %s\n", __FUNCTION__);
	List l = {.head=NULL, .tail=NULL};
	l = append("one", l);
	l = append("two", l);
	free_list(l);
	return 0;
}

// An array of function pointers that contains the test functions.
static int (*const TEST_FUNCS[]) (void) = { 
	test_append_forward, test_append_backward, test_reverse_list_many,
	test_reverse_list_double, test_reverse_list_single, test_insert_before_and_after_forward,
	test_insert_before_and_after_backward, test_free
};

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

int main(void){
	//run_all_tests();
	//List l = {.head=NULL, .tail=NULL};
	//l = append("one", l);
	//l = append("two", l);
	//l = append("three", l);
	//write_binfile(l, "hi.bin");
	List l = read_binfile("hi.bin");
	print_list(l);
	print_list_reverse(l);
	return 0;
}

