#include <vector>
#include <cmath>
#include <iostream>

std::vector<int> printNumbers(int x) {
	std::vector <int> _numbers;
	for (int k = 0; k <= log(x) / log(3); k++) {
		for (int l = 0; l <= log(x) / log(5); l++) {
			for (int m = 0; m <= log(x) / log(7); m++) {
				int number = pow(3, k) * pow(5, l) * pow(7, m);
				if (number <= x) {
					_numbers.push_back(number);
				}
			}
		}
	}
	return _numbers;
}

int main() {
	int x;
	std::cin >> x;
	std::vector<int> numbers = printNumbers(x);
	for (int i = 0; i < numbers.size() - 1; i++)
		std::cout << numbers[i] << ' ';
}