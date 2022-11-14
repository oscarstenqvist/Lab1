#include "analyze.h"
#include "algorithm.h"
#include <math.h> //??
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//
// Private
//
void runSearch(int *list, bool (*f)(const int *, int, int), result_t *buf, int size) {
	int search = 0; // always searching for 0
	clock_t startClock, endClock;
	double totalClock = 0.0;
	for (int times = 0; times < (ITERATIONS * 1000) + 2; times++) {
		startClock = clock();
		(*f)(list, size, search);
		endClock = clock();
		if (times > 1) { // warmpup 2 iterations
			totalClock += endClock - startClock;
		}
	}
	buf->size = size;
	buf->time = (((double)totalClock) / CLOCKS_PER_SEC) / (ITERATIONS * 1000);
}
void runSort(int *list, void (*f)(int *, int), result_t *buf, int size) {
	int listC[size];
	clock_t startClock, endClock;
	double totalClock = 0.0;
	for (int times = 0; times < (ITERATIONS * 3) + 2; times++) {
		for (int i = 0; i < size; i++) { // create copy of original array
			listC[i] = list[i];
		}
		startClock = clock();
		(*f)(listC, size);
		endClock = clock();
		if (times > 1) { // warmp 2 iterations
			totalClock += endClock - startClock;
		}
	}
	buf->size = size;
	buf->time = (((double)totalClock) / CLOCKS_PER_SEC) / (ITERATIONS * 3);
}
void initSequence(int start, int end, int n, int *list) {
	for (int i = 0; i < n; i++) {
		if (start > end) {
			list[i] = start - i;
		} else {
			list[i] = i;
		}
	}
}
void initSameSequence(int value, int n, int *list) {
	for (int i = 0; i < n; i++) {
		list[i] = value;
	}
}
void shuffle(int *list, int n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		int randInt = rand() % n;
		int temp = list[i];
		list[i] = list[randInt];
		list[randInt] = temp;
	}
}
//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n) {
	for (int i = 0; i < n; i++) {
		int s;
		if (a == binary_search_t || a == linear_search_t) {
			s = (int)(SIZE_START * 127) * pow(2, i); // start at 65024 when searching for better results
		} else {
			s = (int)(SIZE_START * pow(2, i));
		}
		int list[s];
		switch (a) {
		case bubble_sort_t:
			if (c == best_t) {
				initSequence(0, s, s, list);
			} else if (c == worst_t) {
				initSequence(s - 1, 0, s, list);
			} else if (c == average_t) {
				initSequence(0, s, s, list); // TAKES LONGER THAN WORST WHY?
				shuffle(list, s);
			}
			runSort(list, bubble_sort, buf + i, s);
			break;
		case insertion_sort_t:
			if (c == best_t) {
				initSequence(0, s, s, list);
			} else if (c == worst_t) {
				initSequence(s - 1, 0, s, list);
			} else if (c == average_t) {
				initSequence(0, s, s, list);
				shuffle(list, s);
			}
			runSort(list, insertion_sort, buf + i, s);
			break;
		case linear_search_t:
			if (c == best_t) {
				initSameSequence(0, s, list); // CHANGE SO THAT IT IS A REAL SEQ and search for random value
			} else if (c == worst_t) {
				initSameSequence(1, s, list);
			} else if (c == average_t) {
				initSameSequence(1, s, list);
				list[s / 2] = 0; // find search in middle
			}
			runSearch(list, linear_search, buf + i, s);
			break;
		case binary_search_t:
			if (c == best_t) {
				initSameSequence(0, s, list);
			} else if (c == worst_t) {
				initSameSequence(1, s, list);
			} else if (c == average_t) {
				initSameSequence(1, s, list);
				list[s - 1] = 0; // find search at last element
			}
			runSearch(list, binary_search, buf + i, s);
			break;
		case quick_sort_t:
			if (c == best_t) {
				initSequence(0, s, s, list); // Best case random?
				shuffle(list, s);
			} else if (c == worst_t) {
				initSequence(0, s, s, list); // Ordered worst case?
			} else if (c == average_t) {
				initSequence(0, s, s, list); // Average case random?
				shuffle(list, s);
			}
			runSort(list, quick_sort, buf + i, s);
			break;
		default:
			break;
		}
	}
}