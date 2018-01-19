#include "common.h"

void append_entry_to_list(struct list *l, void *data){
	struct list_entry *e = calloc(1, sizeof(struct list_entry));
	e->data = data;
	if(l->head == NULL){
		l->head = e;
		l->tail = e;
	} else {
		l->tail->next = e;
		e->prev = l->tail;
		l->tail = e;
	}
}

void remove_entry_from_list(struct list *l, struct list_entry *e){
	if(e == l->head && e == l->tail){
		l->head = NULL;
		l->tail = NULL;
	} else if(e == l->head){
		l->head = e->next;
		e->next->prev = NULL;
	} else if(e == l->tail){
		l->tail = e->prev;
		e->prev->next = NULL;
	} else {
		e->prev->next = e->next;
		e->next->prev = e->prev;
	}
	free(e);
}

// Looks for an entry that has the same data pointer and removes it.
void remove_entry_from_list_by_data(struct list *l, void *data){
	struct list_entry *e = l->head;
	while(e->data != data){
		e = e->next;
	}
	remove_entry_from_list(l, e);
}
