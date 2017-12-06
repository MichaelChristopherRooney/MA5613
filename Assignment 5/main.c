#include <stdlib.h>

#include "list.h"

int main(void){
	List l = {.head=NULL, .tail=NULL};
	l = append("hi", l);
	//l = append("hi1", l);
	//l = append("hi2", l);
	l = insert_before("hi", "bye", l);
	print_list(l);
	print_list_reverse(l);
	l = reverse(l);
	print_list(l);
	print_list_reverse(l);
	return 0;
}
