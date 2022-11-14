#include <stdbool.h>
#include <stdio.h>

bool binary_search(const int *a, int n, int v) { // TODO FIX BINARY SEARCH
	int nStart = n - 1, element;
	double p;
	int nOld = n;
	n = n / 2;
	while (n >= 0 && n <= nStart) {
		element = a[n];
		printf("%d\n", element);
		if (element == v) {
			return true;
		}
		if (n == nStart || n == 0) {
			return false;
		}
		if (v > element) {
			p = 0.75 * nOld;
			n = (int)p;
			nOld = n;
			continue;
		} else {
			p = 0.75 * nOld;
			n = (int)p;
			if (n > nStart) {
				n = nStart;
			}
			nOld = n;
			continue;
		}
	}
	return false;
}
int main() {
	int list[1000];
	for (int i = 0; i < 1000; i++)
		list[i] = i;
	int x = binary_search(list, 1000, 999);
	printf(x ? "Found\n" : "Not found\n");
	return 0;
}