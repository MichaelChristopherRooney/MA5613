#include <stdio.h>
#include <string.h>

void bubblesort(char string[]){
	int no_swaps = 0;
	int str_len = strlen(string);
	while(no_swaps == 0){
		no_swaps = 1;
		int i;
		for(i = 0; i < str_len - 1; i++){
			if(string[i] > string[i + 1]){
				printf("Swapping %c and %c\n", string[i], string[i + 1]);
				char temp = string[i];
				string[i] = string[i + 1];
				string[i + 1] = temp;
				no_swaps = 0;
			}
		}
	}
}

int main(void){
	char s[] = "the quick brown fox jumps over the lazy dog";
	//char s[] = "cba";
	bubblesort(s);
	printf("%s\n", s);
}
