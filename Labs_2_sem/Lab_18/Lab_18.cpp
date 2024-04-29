#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

bool subsetSumZero(const std::vector<int>& numbers) {
    std::vector<int> S = { 0 };

    for (int x : numbers) {
        std::vector<int> newS;

        for (int y : S) {
            int sum = x + y;
            if (sum == 0) {
                return true;
            }
            newS.push_back(sum);
        }

        S.insert(S.end(), newS.begin(), newS.end());
    }

    return false;
}

int main() {
    std::vector<int> numbers = { -7, 5, -3, -2, 8 };

    if (subsetSumZero(numbers)) {
        std::cout << "Yes,there sum exists" << std::endl;
    }
    else {
        std::cout << "No, there doesn't exist" << std::endl;
    }

    return 0;
}