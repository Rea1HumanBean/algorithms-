#include <iostream>
#include <vector>


void sortMerge(std::vector<int>& arr, int a, int b) {
    if (b - a < 2)
        return;
    if (b - a == 2) {
        if (arr[a] > arr[a + 1])
            std::swap(arr[a], arr[a + 1]);
        return;
    }
    sortMerge(arr, a, a + (b - a) / 2);
    sortMerge(arr, a + (b - a) / 2, b);
    std::vector<int> aux_arr;
    int a_1 = a;
    int b_1 = a + (b - a) / 2;
    int a_2 = b_1;
    while (aux_arr.size() < b - a) {
        if (a_1 >= b_1 || (a_2 < b && arr[a_2] <= arr[a_1])) {
            aux_arr.push_back(arr[a_2]);
            a_2++;
        }
        else {
            aux_arr.push_back(arr[a_1]);
            a_1++;
        }
    }
    for (int i = a; i < b; i++)
        arr[i] = aux_arr[i - a];
}

int main() {

    std::vector<int> arr = { 1,3,35,6,5,234,4,754,13,54,123,414,404,1003, 40 };
    sortMerge(arr, 0, arr.size());

    std::cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}