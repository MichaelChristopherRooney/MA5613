#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// A deliberately slow implementation
// Time taken grows exponentially as k increases
int fib(int k){
	if(k == 1 || k == 2){
		return 1;
	}
	return fib(k - 1) + fib(k - 2);
}

// A much faster implementation
// Time taken grows lineraly as k increases
int fib2(int k){
	if(k == 1 || k == 2){
		return 1;
	}
	int i;
	int prev_1 = 1;
	int prev_2 = 1;
	int f = 0;
	for(i = 2; i < k; i++){
		f = prev_1 + prev_2;
		prev_2 = prev_1;
		prev_1 = f;
	}
	return f;
}

// Just calls fib with some timing code around it
void run_fib(int k){
	struct timeval start_time; 
	struct timeval end_time;
	long long time_taken = 0L;
	printf("Using slow version\n");
	gettimeofday(&start_time, NULL);
	int result = fib(k);
	gettimeofday(&end_time, NULL);
	time_taken = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
	printf("Slow version took %lld microseconds and calculated Fibonacci number %d as %d\n", time_taken, k, result);
}

// Just calls fib2 with some timing code around it
void run_fib2(int k){
	struct timeval start_time; 
	struct timeval end_time;
	long long time_taken = 0L;
	printf("Using fast version\n");
	gettimeofday(&start_time, NULL);
	int result = fib2(k);
	gettimeofday(&end_time, NULL);
	time_taken = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
	printf("Fast version took %lld microseconds and calculated Fibonacci number %d as %d\n", time_taken, k, result);
}

// For fibonacci numbers 1 to n inclusive this calculates the time taken for each.
// Each number is calculated 10 times and the time taken is averaged.
// The results are written to a .csv file so they can be graphed
void time_fib(n){
	// To "warm" the cache first
	fib(10);
	struct timeval start_time; 
	struct timeval end_time;
	long long time_taken;
	const int num_runs = 10;
	FILE *fp = fopen("results.csv", "w");
	int i;
	for(i = 1; i <= n; i++){
		time_taken = 0;
		int j;
		for(j = 0; j < num_runs; j++){
			gettimeofday(&start_time, NULL);
			int result = fib(i);
			gettimeofday(&end_time, NULL);
			time_taken += (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
		}
		time_taken = time_taken / num_runs;
		fprintf(fp, "%lld,", time_taken);
		printf("%d took %lld microseconds\n", i, time_taken);
	}
	fclose(fp);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: expected a single int passed as an argument\n");
		return 1;
	}
	int k = atoi(argv[1]);
	if(k == 0){
		printf("Please pass a valid non-zero integer\n");
		return 1;
	}
	run_fib(k);
	run_fib2(k);
}

