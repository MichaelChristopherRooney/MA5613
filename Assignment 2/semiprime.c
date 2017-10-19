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

// A semiprime is a number which can be wrriten in the form p*q where p and q
// are prime [p = q is allowed]
// A semiprime will have only 1, p, q and itself as factors.
// We find the first factors (that are not 1 or the number itself) and test if these are prime.
// If either of the found factors are not prime then the number is not semiprime.
int is_semiprime(int x){
	int result = 0;
	int limit = sqrt(x);
	int i;
	for(i = 2; i <= limit; i++){
		int j = x / i;
		if(x % i == 0 && x % j == 0){
			return is_prime(i) & is_prime(j);
		}
	}
	return 0;
}

#define LIMIT 1000

int main(void){
	int i;
	for(i = 0; i < LIMIT; i++){
		int result = is_semiprime(i);
		if(result == 1){
			printf("%d is semiprime\n", i);
		}
	}	
}
