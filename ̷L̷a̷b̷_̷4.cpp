#include <iostream>
#include <vector>

void sortBubble(std::vector<int>& _arr) {
	for (int i = 0; i < _arr.size() - 1; i++) {
		for (int j = 0; j < _arr.size() - 1; j++) {
			if (_arr[j] > _arr[j + 1]) {
				int bubble = _arr[j];
				_arr[j] = _arr[j + 1];
				_arr[j + 1] = bubble;
			}
		}
	}
}

int main() {
	std::vector<int> arr = { 1,9,32,242,24,2,53,3,10,32 };
	sortBubble(arr);
	for (int i = 0; i < arr.size(); ++i) {
		std::cout << arr[i] << ' ';
	}
}