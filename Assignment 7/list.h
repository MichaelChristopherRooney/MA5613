struct list_entry {
	void *data;
	struct list_entry *next;
	struct list_entry *prev;
};

struct list {
	struct list_entry *head;
	struct list_entry *tail;
};

void append_entry_to_list(struct list *l, void *data);
void remove_entry_from_list(struct list *l, struct list_entry *e);
