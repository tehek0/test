#include <iostream>
#include <vector>

void quicksort(int a, int b, int* arr) {
	if (a >= b)
		return;

	int k = (rand() * rand()) % (b - a + 1) + a;
	int m = arr[k];

	int l = a - 1;
	int r = b + 1;

	while (true) {
		do l++; while (arr[l] < m);
		do r--; while (arr[r] > m);
		if (l >= r)
			break;
		std::swap(arr[l], arr[r]);
	}
	l = r;
	r++;
	quicksort(a, l, arr);
	quicksort(r, b, arr);
}

int main() {
	std::vector<int> arr = { 0, 5, 3, 1, 7, 90, 321, 6, 23, 512, 7902, 173, 2, 6135, 2, 321, 3, 5, 12, 5, 25, 12, 5, 125, 12, 5, 215, 12, 512, 6, 12, 6, 12, 65, 7, 6458756, 8, 568, 56, 856 };
	quicksort(0, arr.size() - 1, arr.data());
	for (auto i : arr) {
		std::cout << i << " ";
	}
}