typedef struct Cell_struct {
	struct Cell_struct *next;
	struct Cell_struct *prev;
	char *word;
} Cell;

typedef struct {
	struct Cell_struct *head;
	struct Cell_struct *tail;
} List;

List append(const char *word, List l);
void print_list(const List l);
void free_list(List l);
List insert_before(const char *find, const char *word, List l);
