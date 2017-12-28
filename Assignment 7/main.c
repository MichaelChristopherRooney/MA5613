#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Takes a line from the input file, tokenises it and then creates vertices from it.
// Example: "0;1;2\n" is split into "0", "1", "2", which is taken to be mean that 
// vertex 0 is connected to vertices 1 and 2.
// Tokens are ';' and '\n'
static int parse_vertices_from_line(char *line){
	char *tok = strtok(line, ";\n");
	if(tok == NULL){
		printf("Error: empty line.\n");
		return 1;
	}
	printf("Found token: %s\n", tok);
	while((tok = strtok(NULL, ";\n")) != NULL){
		printf("Found token: %s\n", tok);
	}
	return 0;
}

static int read_vertices_from_file(char *filename){
	FILE *fp = fopen(filename, "r");
	if(!fp){
		printf("Error: cannot open file: %s\n", filename);
		return 1;
	}
	size_t size = 256;
	char *buffer = malloc(sizeof(char) * size);
	while(1){
		getline(&buffer, &size, fp);
		if(feof(fp)){
			break;
		}
		printf("Line is: %s", buffer);
		parse_vertices_from_line(buffer);
	}
	fclose(fp);
	return 0;
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: expected filename passed as arg!\n");
		return 1;
	}
	char *filename = argv[1];
	printf("Filename is: %s\n", filename);
	if(read_vertices_from_file(filename) == 1){
		return 1;
	}	
	return 0;
}
