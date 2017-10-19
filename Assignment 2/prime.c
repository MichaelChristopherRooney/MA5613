#include <math.h>
#include <stdio.h>

int is_prime(int x){
	if(x < 2){
		return 0;
	}
	int limit = sqrt(x);
	int i;	
	for(i = 2; i <= limit; i++){
		if(x % i == 0){
			return 0;
		}
	}
	return 1;
}

int main(void){
	int i;
	for(i = 0; i < 1000; i++){
		if(is_prime(i) == 1){
			printf("%d is prime\n", i);
		}
	}
	return 0;
}
