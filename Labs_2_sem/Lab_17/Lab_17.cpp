#include <iostream>
#include <vector>
#include <algorithm>

int minBoxesDP(std::vector<int>& items, int boxCapacity) {
    int n = items.size();
    if (n == 0)
        return 0;

    std::sort(items.rbegin(), items.rend());

    int minNumBoxes = 0;
    while (!items.empty()) {
        int curCap = 0;
        std::vector<int> selectedItems;

        for (int i = 0; i < items.size(); i++) {
            if (curCap + items[i] <= boxCapacity) {
                curCap += items[i];
                selectedItems.push_back(items[i]);
            }
        }

        for (int item : selectedItems) {
            auto it = std::find(items.begin(), items.end(), item);
            if (it != items.end()) {
                items.erase(it);
            }
        }
        minNumBoxes++;
    }

    return minNumBoxes;
}


int main() {
    std::vector<int> items = { 1, 1, 2, 2, 2, 2, 7 };
    int boxCapacity = 10;

    int minNumBoxes = minBoxesDP(items, boxCapacity);
    std::cout << "Minimum number of boxes required: " << minNumBoxes << std::endl;

    return 0;
}