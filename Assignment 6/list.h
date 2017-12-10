typedef struct Cell_struct {
	struct Cell_struct *next;
	struct Cell_struct *prev;
	char *word;
} Cell;

typedef struct {
	struct Cell_struct *head;
	struct Cell_struct *tail;
} List;

List read_textfile(char *filename);
List append(char *word, List l);
void print_list(List l);
void free_list(List l);
List insert_before(char *find, char *word, List l);
List insert_after(char *find, char *word, List l);
void print_list_reverse(List l);
List reverse(List l);
void write_binfile(List l, char *filename);
List read_binfile(char *filename);
