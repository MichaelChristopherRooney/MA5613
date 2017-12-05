#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>
#include <omp.h>

#define GRID_SIZE 40
#define NUM_ITERATIONS 100

#define BLACK "\x1B[30m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

#define SLEEP_BETWEEN_PRINTS 0
#define PRINT_RESULTS 1
#define RECORD_TIME 0

#define NUM_THREADS 4

static int grid_1[GRID_SIZE][GRID_SIZE];
static int grid_2[GRID_SIZE][GRID_SIZE];

static int (*old_grid)[GRID_SIZE] = grid_1;
static int (*cur_grid)[GRID_SIZE] = grid_2;
// Used for swapping grids
static int (*temp)[GRID_SIZE];

static void clear_old_grid(){
#if PRINT_RESULTS
	int i;
	for(i = 0; i < GRID_SIZE; i++){
		fputs("\033[A\033[2K",stdout);
	}
	rewind(stdout);
	ftruncate(1,0);
#endif
}

static void print_grid() {
#if PRINT_RESULTS
	int x, y;
	for (x = 0; x < GRID_SIZE; x++) {
		for (y = 0; y < GRID_SIZE; y++) {
			if(cur_grid[x][y] == 1){
				printf(WHITE "\u25A0" RESET);
			} else {
				printf(BLACK "\u25A0" RESET);
			}
		}
		printf("\n");
	}
#endif
}

// Note: uses the old grid
static int is_cell_alive(int x, int y) {
	if (x == -1) {
		x = GRID_SIZE - 1;
	} else if (x == GRID_SIZE) {
		x = 0;
	}
	if (y == -1) {
		y = GRID_SIZE - 1;
	} else if (y == GRID_SIZE) {
		y = 0;
	}
	return old_grid[x][y];
}

static int determine_cell_next_state(int x, int y, int currently_alive) {
	int count = 0;
	// Unrolled compared to the naive approach.
	count += is_cell_alive(x - 1, y - 1);
	count += is_cell_alive(x, y - 1);
	count += is_cell_alive(x + 1, y - 1);
	count += is_cell_alive(x - 1, y + 1);
	count += is_cell_alive(x, y + 1);
	count += is_cell_alive(x + 1, y + 1);
	count += is_cell_alive(x - 1, y);
	count += is_cell_alive(x + 1, y);
	if ((currently_alive == 1 && count == 2) || count == 3) {
		return 1;
	} else {
		return 0;
	}
}

// Uses pointers to swap the grids.
static void swap_grids(){
	temp = cur_grid;
	cur_grid = old_grid;
	old_grid = temp;
}

static void run_tick() {
	swap_grids();	
	int x;
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel for
	for (x = 0; x < GRID_SIZE; x++) {
			// unrolled loop entirely
			// ugly, but fast
			cur_grid[x][0] = determine_cell_next_state(x, 0, old_grid[x][0]);
			cur_grid[x][1] = determine_cell_next_state(x, 1, old_grid[x][1]);
			cur_grid[x][2] = determine_cell_next_state(x, 2, old_grid[x][2]);
			cur_grid[x][3] = determine_cell_next_state(x, 3, old_grid[x][3]);
			cur_grid[x][4] = determine_cell_next_state(x, 4, old_grid[x][4]);			
			cur_grid[x][5] = determine_cell_next_state(x, 5, old_grid[x][5]);
			cur_grid[x][6] = determine_cell_next_state(x, 6, old_grid[x][6]);
			cur_grid[x][7] = determine_cell_next_state(x, 7, old_grid[x][7]);
			cur_grid[x][8] = determine_cell_next_state(x, 8, old_grid[x][8]);
			cur_grid[x][9] = determine_cell_next_state(x, 9, old_grid[x][9]);
			cur_grid[x][10] = determine_cell_next_state(x, 10, old_grid[x][10]);
			cur_grid[x][11] = determine_cell_next_state(x, 11, old_grid[x][11]);
			cur_grid[x][12] = determine_cell_next_state(x, 12, old_grid[x][12]);
			cur_grid[x][13] = determine_cell_next_state(x, 13, old_grid[x][13]);
			cur_grid[x][14] = determine_cell_next_state(x, 14, old_grid[x][14]);			
			cur_grid[x][15] = determine_cell_next_state(x, 15, old_grid[x][15]);
			cur_grid[x][16] = determine_cell_next_state(x, 16, old_grid[x][16]);
			cur_grid[x][17] = determine_cell_next_state(x, 17, old_grid[x][17]);
			cur_grid[x][18] = determine_cell_next_state(x, 18, old_grid[x][18]);
			cur_grid[x][19] = determine_cell_next_state(x, 19, old_grid[x][19]);
			cur_grid[x][20] = determine_cell_next_state(x, 20, old_grid[x][20]);
			cur_grid[x][21] = determine_cell_next_state(x, 21, old_grid[x][21]);
			cur_grid[x][22] = determine_cell_next_state(x, 22, old_grid[x][22]);
			cur_grid[x][23] = determine_cell_next_state(x, 23, old_grid[x][23]);
			cur_grid[x][24] = determine_cell_next_state(x, 24, old_grid[x][24]);			
			cur_grid[x][25] = determine_cell_next_state(x, 25, old_grid[x][25]);
			cur_grid[x][26] = determine_cell_next_state(x, 26, old_grid[x][26]);
			cur_grid[x][27] = determine_cell_next_state(x, 27, old_grid[x][27]);
			cur_grid[x][28] = determine_cell_next_state(x, 28, old_grid[x][28]);
			cur_grid[x][29] = determine_cell_next_state(x, 29, old_grid[x][29]);
			cur_grid[x][30] = determine_cell_next_state(x, 30, old_grid[x][30]);
			cur_grid[x][31] = determine_cell_next_state(x, 31, old_grid[x][31]);
			cur_grid[x][32] = determine_cell_next_state(x, 32, old_grid[x][32]);
			cur_grid[x][33] = determine_cell_next_state(x, 33, old_grid[x][33]);
			cur_grid[x][34] = determine_cell_next_state(x, 34, old_grid[x][34]);			
			cur_grid[x][35] = determine_cell_next_state(x, 35, old_grid[x][35]);
			cur_grid[x][36] = determine_cell_next_state(x, 36, old_grid[x][36]);
			cur_grid[x][37] = determine_cell_next_state(x, 37, old_grid[x][37]);
			cur_grid[x][38] = determine_cell_next_state(x, 38, old_grid[x][38]);
			cur_grid[x][39] = determine_cell_next_state(x, 39, old_grid[x][39]);
	}
	clear_old_grid();
	print_grid();
#if SLEEP_BETWEEN_PRINTS
	sleep(1);
#endif
}

static void init_grid() {
	int x, y;
	for (x = 0; x < GRID_SIZE; x++) {
		for (y = 0; y < GRID_SIZE; y++) {
			cur_grid[x][y] = (int) rand() % 2;
		}
	}
}

int main() {
	init_grid();
	print_grid();
#if RECORD_TIME
	struct timeval start_time;
	struct timeval end_time;
	long long time_taken;
	gettimeofday(&start_time, NULL);
#endif
	int i;
	for (i = 0; i < NUM_ITERATIONS; i = i + 10) {
		// unrolled loop
		run_tick();
		run_tick();
		run_tick();
		run_tick();
		run_tick();
		run_tick();
		run_tick();
		run_tick();
		run_tick();
		run_tick();
	}
#if RECORD_TIME
	gettimeofday(&end_time, NULL);
	time_taken = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
	printf("Time taken: %lld microseconds.\n", time_taken);
#endif
	return 0;
}
