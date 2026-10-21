#include <iostream>
#include <vector>

void comb_sort(int* arr, int n) {
    int gap = n;
    float k = 1.3f;
    bool swapped = true;

    while (gap != 1)
    {
        gap = gap / k;
        gap = (gap < 1 ? 1 : (gap == 9 || gap == 10 ? 11 : gap));

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

void shell_sort(int* arr, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
    }
}

void radix_sort(int* arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    for (int exp = 1; max / exp > 0; exp *= 10) {
        int* output = new int[n];
        int i, count[10] = { 0 };

        for (i = 0; i < n; i++)
            count[(arr[i] / exp) % 10]++;

        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (i = 0; i < n; i++) {
            arr[i] = output[i];
        }

        delete[] output;
    }
}

void heapify(int arr[], int n, int i)
{
    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}
void heap_sort(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right) {

    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void merge_sort(std::vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


int main() {
    /*int arr[10] = { 8, 2, 7, 4, 3, 1, 10, 50, 25, 3 };
    int size = 10;
    heap_sort(arr, size);*/
    std::vector<int> arr = {8, 2, 7, 4, 3, 1, 10, 50, 25, 3};
    merge_sort(arr, 0, arr.size() - 1);
    for (auto x : arr) {
        std::cout << x << " ";
    }
}