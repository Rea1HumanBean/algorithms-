#include <iostream>
#include <vector>

void quickSort(std::vector<int>& arr, int start, int end) {
    if (start < end) {
        int current = start;
        for (int i = start + 1; i <= end; i++) {
            if (arr[i] < arr[start]) {
                current++;
                std::swap(arr[current], arr[i]);
            }
        }
        std::swap(arr[start], arr[current]);

        quickSort(arr, start, current - 1);
        quickSort(arr, current + 1, end);
    }
}

int main() {
    std::vector<int> arr = { 9, 7, 5, 11, 12, 2, 14, 3, 1, 6 };

    quickSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
}