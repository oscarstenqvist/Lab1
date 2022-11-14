#include "ui.h"
#include "analyze.h"
#include "io.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>

//
// Private
//
static void ui_invalid_input() {
	printf("info> bad input\n");
}

static void ui_exit() {
	printf("info> bye\n");
}

static char ui_get_choice() {
	char buf[3];

	printf("input> ");
	return read_line(buf, 3) ? buf[0] : 0;
}

static void ui_line(char c, int n) {
	while (n-- > 0) {
		putchar(c);
	}
	putchar('\n');
}

static void ui_menu_options(const char *options[], int num_options) {
	int i;

	for (i = 0; i < num_options; i++) {
		printf("    %c) %s\n", 'a' + i, options[i]);
	}
}

static void ui_menu() {
	const char *options[] = {
		"Menu",	  // A
		"Exit\n", // B

		"Bubble sort best case",	  // C
		"Bubble sort worst case",	  // D
		"Bubble sort average case\n", // E

		"Linear search best case",		// F
		"Linear search worst case",		// G
		"Linear search average case\n", // H

		"Insertion sort best case",		 // I
		"Insertion sort worst case",	 // J
		"Insertion sort average case\n", // K

		"Binary search best case",		// L
		"Binary search worst case",		// M
		"Binary search average case\n", // N

		"Quick sort best case",		  // O
		"Quick sort worst case",	  // P
		"Quick sort average case\n"}; // Q

	ui_line('=', MENU_WIDTH);
	ui_menu_options(options, sizeof(options) / sizeof(char *));
	ui_line('-', MENU_WIDTH);
}

static void ui_result(char *a, char *c, result_t *result) {
	ui_line('*', MENU_WIDTH * 3);
	printf("\t\t\t %s: %s\n", a, c);
	ui_line('~', MENU_WIDTH * 3);
	printf("size\ttime T(s)\tT/logn\t\tT/n\t\tT/nlogn\t\tT/n^2\t\tT/n^3\n");
	double timeLog, timeN, timeNLog, timeN2, timeN3;
	for (int i = 0; i < RESULT_ROWS; i++) {
		result_t r = result[i];
		int n = r.size;
		double t = r.time;
		timeLog = t / log(n);
		timeN = t / n;
		timeNLog = t / (n * log(n));
		timeN2 = t / pow(n, 2);
		timeN3 = t / pow(n, 3);
		printf("%d\t%e\t%e\t%e\t%e\t%e\t%e\n", n, t, timeLog, timeN, timeNLog, timeN2, timeN3);
	}
}

//
// Public
//
void ui_run() {
	bool running, show_menu;
	result_t result[RESULT_ROWS];

	show_menu = true;
	running = true;
	while (running) {
		if (show_menu) {
			show_menu = false;
			ui_menu();
		}
		switch (ui_get_choice()) {
		// House keeping
		case 'a':
			show_menu = true;
			break;
		case 'b':
			running = false;
			break;
		// Bubble sort
		case 'c':
			benchmark(bubble_sort_t, best_t, result, RESULT_ROWS);
			ui_result("Bubble sort", "Best case", result);
			break;
		// Invalid input
		case 'd':
			benchmark(bubble_sort_t, worst_t, result, RESULT_ROWS);
			ui_result("Bubble sort", "Worst case", result);
			break;
		case 'e':
			benchmark(bubble_sort_t, average_t, result, RESULT_ROWS);
			ui_result("Bubble sort", "Average case", result);
			break;
		case 'f':
			benchmark(linear_search_t, best_t, result, RESULT_ROWS);
			ui_result("Linear search", "Best case", result);
			break;
		case 'g':
			benchmark(linear_search_t, worst_t, result, RESULT_ROWS);
			ui_result("Linear search", "Worst case", result);
			break;
		case 'h':
			benchmark(linear_search_t, average_t, result, RESULT_ROWS);
			ui_result("Linear search", "Average case", result);
			break;
		case 'i':
			benchmark(insertion_sort_t, best_t, result, RESULT_ROWS);
			ui_result("Insertion sort", "Best case", result);
			break;
		case 'j':
			benchmark(insertion_sort_t, worst_t, result, RESULT_ROWS);
			ui_result("Insertion sort", "Worst case", result);
			break;
		case 'k':
			benchmark(insertion_sort_t, average_t, result, RESULT_ROWS);
			ui_result("Insertion sort", "Average case", result);
			break;
		case 'l':
			benchmark(binary_search_t, best_t, result, RESULT_ROWS);
			ui_result("Binary search", "Best case", result);
			break;
		case 'm':
			benchmark(binary_search_t, worst_t, result, RESULT_ROWS);
			ui_result("Binary search", "Worst case", result);
			break;
		case 'n':
			benchmark(binary_search_t, average_t, result, RESULT_ROWS);
			ui_result("Binary search", "Average case", result);
			break;
		case 'o':
			benchmark(quick_sort_t, best_t, result, RESULT_ROWS);
			ui_result("Quick sort", "Best case", result);
			break;
		case 'p':
			benchmark(quick_sort_t, worst_t, result, RESULT_ROWS);
			ui_result("Quick sort", "Worst case", result);
			break;
		case 'q':
			benchmark(quick_sort_t, average_t, result, RESULT_ROWS);
			ui_result("Quick sort", "Average case", result);
			break;
		default:
			show_menu = false;
			ui_invalid_input();
			break;
		}
	}
	ui_exit();
}
