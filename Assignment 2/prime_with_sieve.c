#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define LIMIT 1000

// To check if a number is prime use it as an index into this array
// Example: primes[0] is false and primes[2] is true
static bool primes[LIMIT];

// We default all values in the array to true (except 0 and 1)
void init_prime_array(){
	int i;
	for(i = 2; i < LIMIT; i++){
		primes[i] = true;
	}
	for(i = 2; i < LIMIT;){
		primes[i] = true;
		int j;
		// Mark all multiples or i as non-rpime
		for(j = i + i; j < LIMIT; j = j + i){
			primes[j] = false;
		}
		i++;
		// Increment i until we find the next number that is still marked prime
		while(i < LIMIT && primes[i] == false){
			printf("%d\n", i);
			i++;		
		}
	}
}

int is_prime(int x){
	if(primes[x] == true){
		return 1;
	} 
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
