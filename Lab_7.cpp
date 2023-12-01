#include <iostream>
#include <vector>

void sortShell(std::vector<int>& _arr) {
    for (int step = _arr.size() / 2; step > 0; step /= 2) {
        for (int i = step; i < _arr.size(); ++i) {
            int temp = _arr[i];
            int j;
            for (j = i; j >= step && _arr[j - step] > temp; j -= step) {
                _arr[j] = _arr[j - step];
            }
            _arr[j] = temp;
        }
    }
};

int main() {
    std::vector<int> arr = { 1,50,12,54,34,23,5,13,4,10,15,97,43,100 };
    sortShell(arr);

    for (int i = 0; i < arr.size(); i++)
        std::cout << arr[i] << ' ';
}