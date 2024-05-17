#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Thing {
    std::string name;
    int weight;
    int cost;
public:
    Thing(std::string _name, int _weight, int _cost) : name(_name), weight(_weight), cost(_cost) {}

    int getWeight() const {
        return weight;
    }
    int getCost() const {
        return cost;
    }

    std::string getName() const {
        return name;
    }
};

class Backpack {
    std::vector<std::vector<int>> dp;
    std::vector<Thing> things;
    int capacity;

public:
    Backpack(int _capacity) : capacity(_capacity) {}

    void selectedThings(const std::vector<Thing>& allThings) {
        things = allThings;
        dp.assign(things.size() + 1, std::vector<int>(capacity + 1, 0));

        for (int i = 1; i <= things.size(); ++i) {
            for (int w = 0; w <= capacity; ++w) {
                if (things[i - 1].getWeight() <= w) {
                    dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - things[i - 1].getWeight()] + things[i - 1].getCost());
                }
                else {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
    }

    void print() {
        int w = capacity;
        std::cout << "Selected items:\n";
        for (int i = things.size(); i > 0 && w >= 0; --i) {
            if (dp[i][w] != dp[i - 1][w]) {
                std::cout << "Name: " << things[i - 1].getName() << ", Weight: " << things[i - 1].getWeight() << ", Value: " << things[i - 1].getCost() << "\n";
                w -= things[i - 1].getWeight();
            }
        }
        std::cout << "Total cost: " << dp[things.size()][capacity] << "\n";
    }
};

int main() {
    std::vector<Thing> things{
        {"thing_1", 10, 5 },
        {"thing_2", 20, 8 },
        {"thing_3", 30, 10},
        {"thing_4", 40, 7 },
        {"thing_5", 50, 40},
        {"thing_6", 60,200},
        {"thing_7", 7, 530},
        {"thing_8", 8,  1 },
        {"thing_9", 9,  43}
    };

    Backpack backpack(120);
    backpack.selectedThings(things);
    backpack.print();
    return 0;
}