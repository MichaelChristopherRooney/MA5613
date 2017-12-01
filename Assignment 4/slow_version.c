#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/time.h>

#define GRID_SIZE 40
#define NUM_ITERATIONS 100

#define BLACK "\x1B[30m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

#define SLEEP_BETWEEN_PRINTS 0
#define PRINT_RESULTS 1
#define RECORD_TIME 0

static int old_grid[GRID_SIZE][GRID_SIZE];
static int cur_grid[GRID_SIZE][GRID_SIZE];

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

// Points to search around a given cell.
// These are to be used with the same index.
// Example: index 1 should give (x + 0, x + (-1)), to check above the current cell.
static const int x_mod[8] = { -1, 0, 1, -1, 0, 1, -1, 1 };
static const int y_mod[8] = { -1, -1, -1, 1, 1, 1, 0, 0 };

static int determine_cell_next_state(int x, int y, int currently_alive) {
	int count = 0;
	for (int i = 0; i < 8; i++) {
		count += is_cell_alive(x + x_mod[i], y + y_mod[i]);
	}
	if ((currently_alive == 1 && count == 2) || count == 3) {
		return 1;
	} else {
		return 0;
	}
}

static void run_tick() {
	// Naive approach - copy memory instead of using a pointer to swap the grids.
	memcpy(old_grid, cur_grid, sizeof(int) * GRID_SIZE * GRID_SIZE);	
	int x, y;
	for (x = 0; x < GRID_SIZE; x++) {
		for (y = 0; y < GRID_SIZE; y = y + 1) {
			cur_grid[x][y] = determine_cell_next_state(x, y, old_grid[x][y]);
		}
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
	for (i = 0; i < NUM_ITERATIONS; i++) {
		run_tick();
	}
#if RECORD_TIME
	gettimeofday(&end_time, NULL);
	time_taken = (end_time.tv_sec - start_time.tv_sec) * 1000000L + (end_time.tv_usec - start_time.tv_usec);
	printf("Time taken: %lld microseconds.\n", time_taken);
#endif
	return 0;
}
