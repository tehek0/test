#include <iostream>

void comb_sort(int* arr, int n) {
    int gap = n;
    float k = 1.3f;
    bool swapped = true;

    while (gap != 1)
    {
        gap = gap / k;
        gap = (gap < 1 ? 1 : (gap == 9 || gap == 10? 11 : gap));

        for (int i = 0; i < n - gap; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                std::swap(arr[i], arr[i + gap]);
            }
        }
    }
}

void insertion_sort(int* arr, int n) {
	for (int i = 1; i < n; i++)
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--) {
            std::swap(arr[j], arr[j - 1]);
		}
}

void selection_sort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++)
    {
        int min_index = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_index])
            {
                min_index = j;
            }
        }
        if (min_index != i)
        {
            std::swap(arr[i], arr[min_index]);
        }
    }
}
void shell_sort(int* arr, int n);
void radix_sort(int* arr, int n);
void heap_sort(int* arr, int n);
void merge_sort(int* arr, int n);


int main() {
	int arr[10] = { 8, 2, 7, 4, 3, 1, 10, 50, 25, 3 };
	int size = 10;
	comb_sort(arr, size);
	for (auto x : arr) {
		std::cout << x << " ";
	}
}