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

	int getWeight() {
		return weight;
	}
	int getCost() {
		return cost;
	}

	std::string getName() {
		return name;
	}
};

class Backpack {
	std::vector<Thing> things;
	int capacity;
	int max_cost;

	static bool compareItems(Thing item1, Thing item2) {
		double ratio1 = static_cast<double>(item1.getCost()) / item1.getWeight();
		double ratio2 = static_cast<double>(item2.getCost()) / item2.getWeight();
		return ratio1 > ratio2;
	};

public:
	Backpack(int _capacity) : capacity(_capacity) {}

	void selectedThings(const std::vector<Thing>& allThings) {
		std::vector<Thing> sortedItems = allThings;
		int currentWeight = 0;
		std::sort(sortedItems.begin(), sortedItems.end(), compareItems);


		for (auto& item : sortedItems) {
			if (currentWeight + item.getWeight() <= capacity) {
				things.push_back(item);
				currentWeight += item.getWeight();
			}
		}
	};

	void print() {
		int cost = 0;
		int weight = 0;
		std::cout << "Selected items:\n";
		for (auto& item : things) {
			std::cout << "Name: " << item.getName() << ", Weight: " << item.getWeight() << ", Value: " << item.getCost() << "\n";
			cost += item.getCost();
			weight += item.getWeight();
		}
		std::cout << "Total cost: " << cost << "\n";
		std::cout << "Total weight: " << weight << "\n";
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

	Backpack Backpack(120);

	Backpack.selectedThings(things);
	Backpack.print();
	return 0;
}