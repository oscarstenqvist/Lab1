#include "algorithm.h"
#include <stdio.h> //DEBUG REMOVE
//
// Private
//
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
int partition(int *a, int low, int high) {
	int pivot = a[high];
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (a[j] < pivot) {
			i++;
			swap(&a[i], &a[j]);
		}
	}
	swap(&a[i + 1], &a[high]);
	return i + 1;
}
void qSort(int *a, int low, int high) {
	if (low < high) {
		int partitionIndex = partition(a, low, high);
		qSort(a, low, partitionIndex - 1);
		qSort(a, partitionIndex + 1, high);
	}
}
//
// Public
//
void bubble_sort(int *a, int n) {
	for (int curr = 0; curr < n - 1; ++curr) {
		int swapped = 0;
		for (int i = 0; i < n - curr - 1; ++i) {
			if (a[i] > a[i + 1]) {
				swap(&a[i], &a[i + 1]);
				swapped = 1;
			}
		}
		if (swapped == 0) {
			break;
		}
	}
}

void insertion_sort(int *a, int n) {
	int k, j;
	for (int i = 1; i < n; i++) {
		k = a[i];
		j = i - 1;
		while (j >= 0 && a[j] > k) {
			a[j + 1] = a[j];
			j = j - 1;
		}
		a[j + 1] = k;
	}
}

void quick_sort(int *a, int n) {
	qSort(a, 0, n);
}

bool linear_search(const int *a, int n, int v) {
	for (int i = 0; i < n; i++) {
		if (a[i] == v) {
			return true;
		}
	}
	return false;
}

bool binary_search(const int *a, int n, int v) {
	n = n - 1;
	int nStart = n, element;
	n = n / 2;
	while (n >= 0 && n <= nStart) {
		element = a[n];
		if (element == v) {
			return true;
		}
		if (element > v) {
			n = n / 2;
			break;
		} else {
			n = n * (3 / 2);
			if (n > nStart) {
				n = nStart;
			}
			break;
		}
	}
	return false;
	/*int nOld = n;
	n = n / 2;
	int element = a[n];
	if (element == v) {
		return true;
	}
	if (n == 0) {
		return false;
	}
	if (element > v) {
		binary_search(a, n, v);
	} else {
		n = nOld - (n / 4);
		// n = n * 4;
		binary_search(a, n, v);
	}
	return false;*/
}
