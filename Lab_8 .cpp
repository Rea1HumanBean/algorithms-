#include <iostream>
#include <vector>
#include <cmath>

int findExp(int _a) {
    int maxExp = 0;
    while (_a > 0) {
        maxExp++;
        _a /= 10;
    }
    return maxExp;
}

int findMaxExp(std::vector<int> _arr) {
    int max = _arr[0];
    for (int i = 1; i < _arr.size(); i++) {
        if (_arr[i] > max) {
            max = _arr[i];
        }
    }
    return  findExp(max);
}


void sortRadix(std::vector<int>& _arr) {
    int maxExp = findMaxExp(_arr);
    std::vector<int> output;

    for (int exp = 0; exp <= maxExp; exp++) {
        for (int j = 0; j < 10; j++) {
            for (int i = 0; i < _arr.size(); i++) {
                int radixInt = (int)(_arr[i] / int(pow(10, exp)) % 10);
                if (radixInt == j)
                    output.push_back(_arr[i]);
            }
        }
        _arr = output;
        output.clear();
    }
}

int main() {

    std::vector<int> arr = { 1,3,35,6,5,234,4,754,13,54,123,414,404,1003, 40, 80 };
    sortRadix(arr);

    std::cout << "Sorted array: ";
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}