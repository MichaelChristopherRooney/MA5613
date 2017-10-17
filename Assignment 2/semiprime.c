#include <math.h>
#include <stdio.h>

#define LIMIT 1000

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

// This function will find only factors of x that are not 1 or x.
// It returns 1 if factors that meet this condition are found, otherwise 0.
int get_factors_besides_one_and_x(int x, int *f1, int *f2){
	int limit = sqrt(x); // TODO: double check this
	int i;
	for(i = 2; i <= limit; i++){
		int j = x / i;
		if(x % i == 0 && x % j == 0){
			*f1 = i;
			*f2 = j;
			return 1;
		}
	}
	return 0;
}

// A semiprime is a number which can be wrriten in the form p*q where p and q
// are prime [p = q is allowed]
// A semiprime will have only 1, p, q and itself as factors.
// We find the first factors and test if these are prime.
// If either of the found factors are not prime then the number is not semiprime.
int is_semiprime(int x){
	int f1, f2; // factors
	int result = get_factors_besides_one_and_x(x, &f1, &f2);
	if(result == 1){
		//printf("For %d found factors %d and %d\n", x, f1, f2);
		return is_prime(f1) & is_prime(f2);
	} else {
		//printf("No factors besides 1 and itself found for %d\n", x);
	}

}

int main(void){
	int i;
	for(i = 0; i < LIMIT; i++){
		int result = is_semiprime(i);
		if(result == 1){
			printf("%d is semiprime\n", i);
		}
	}	
}
