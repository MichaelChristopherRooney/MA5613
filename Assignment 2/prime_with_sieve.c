#include <math.h>
#include <stdio.h>

#define LIMIT 1000

// To check if a number is prime use it as an index into this array
// Example: primes[0] is 0 and primes[2] is 1
static int primes[LIMIT];

// We default all values in the array to 1 (except 0 and 1)
// Then non-primes are marked as 0
void init_prime_array(){
	int i;
	for(i = 2; i < LIMIT; i++){
		primes[i] = 1;
	}
	for(i = 2; i < LIMIT;){
		primes[i] = 1;
		int j;
		// Mark all multiples or i as non-prime
		for(j = i + i; j < LIMIT; j = j + i){
			primes[j] = 0;
		}
		i++;
		// Increment i until we find the next number that is still marked prime
		while(i < LIMIT && primes[i] == 0){
			i++;		
		}
	}
}

int is_prime(int x){
	return primes[x];
}

int main(void){
	init_prime_array();
	int i;
	for(i = 0; i < LIMIT; i++){
		if(is_prime(i) == 1){
			printf("%d is prime\n", i);
		}
	}
	return 0;
}
