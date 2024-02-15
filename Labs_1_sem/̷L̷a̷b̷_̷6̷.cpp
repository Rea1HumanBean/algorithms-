#include <iostream>
#include <vector>

void sortInsertion(std::vector<int>& _arr) {
	for (int i = 0; i < _arr.size(); i++) {
		for (int j = i; j > 0 && _arr[j - 1] > _arr[j]; j--) {
			std::swap(_arr[j - 1], _arr[j]);
		}
	}
}

int main() {
	std::vector<int> arr = { 1,9,32,242,24,2,53,3,10,32 };
	sortInsertion(arr);
	for (int i = 0; i < arr.size(); ++i) {
		std::cout << arr[i] << ' ';
	}
}