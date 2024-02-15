#include <iostream>
#include <string>

bool IsWithoutMistake(const std::string& tested) {
	std::string open  = { '{','(','[' };
	std::string close = { '}',')',']' };
	std::string bracket;
	int i = 0, count = 0;
	if (open.find(tested[i]) != std::string::npos) {
		bracket += tested[i];
		i++;
		count++;
		while (i < tested.length()) {
			if ((bracket.length() != 0) && close.find(tested[i]) == open.find(bracket.back())) {
				bracket.pop_back();
				count--;
			}
			if (open.find(tested[i]) != std::string::npos) {
				bracket += tested[i];
				count++;
			}
			i++;
		}
		if (bracket.length() == 0)
			return true;
	}
	return false;
}

int main() {
	std::string a = "([({)}())]";
	std::string b = "})[({}()){";
	std::cout << IsWithoutMistake(a) << std::endl;
	std::cout << IsWithoutMistake(b) << std::endl;
}