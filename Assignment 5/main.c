#include <stdlib.h>

#include "list.h"

int main(void){
	List l;
	l.head = NULL;
	l.tail = NULL;
	l = append("hi", l);
	l = append("hi1", l);
	l = append("hi2", l);
	l = insert_before("hi2", "bye", l);
	print_list(l);
	return 0;
}