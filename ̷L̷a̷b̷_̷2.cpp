#include <iostream>
#include <string>

double performOperation(double num1, double num2, char oper) {
	switch (oper) {
	case '+':
		return num1 + num2;
	case '-':
		return num1 - num2;
	case '*':
		return num1 * num2;
	case '/':
		if (num2 != 0)
			return num1 / num2;
		else
			throw std::runtime_error("Деление на ноль!");
	}
}

std::string equals(std::string& _expression) {
	std::string operators = "+-/*", close = "}])", open = "{[(";
	bool last_Number = false;
	for (int i = 0; i < _expression.length(); i++) {
		if (_expression[i] == '-' && (i == 0 || operators.find(_expression[i - 1]) != std::string::npos))
			_expression[i] = '$';
	}
	for (int i = 0; i < _expression.length(); i++) {
		if (_expression[i] == '*' || _expression[i] == '/') {
			std::string Digital_1 = "", Digital_2 = "";
			int j = i - 1, k = i + 1;
			while (isdigit(_expression[j]) || _expression[j] == '.') {
				Digital_1 += _expression[j];
				if (j == 0)
					break;
				j--;
			}
			for (int s = 0; s < Digital_1.length() / 2; s++) {
				std::swap(Digital_1[s], Digital_1[Digital_1.length() - 1 - s]);
			}
			if (_expression[j] == '$') {
				Digital_1.insert(0, 1, '-');
				j--;
			}
			if (_expression[i + 1] == '$') {
				Digital_2 = '-';
				k++;
			}
			while (isdigit(_expression[k]) || _expression[k] == '.') {
				Digital_2 += _expression[k];
				k++;
			}
			double result = performOperation(std::stod(Digital_1), std::stod(Digital_2), _expression[i]);
			std::string _result = std::to_string(result);
			while (_result.back() == '0' || _result.back() == '.') {
				if (_result.back() == '.') {
					_result.erase(_result.length() - 1);
					break;
				}
				_result.erase(_result.length() - 1);
			}
			if (j == 0)
				_expression.replace(j, k - j, _result);
			else
				_expression.replace(j + 1, k - j - 1, _result);
			i = 0;
		}
	}

	for (int i = 0; i < _expression.length(); i++) {
		if (_expression[i] == '+' || _expression[i] == '-') {
			if (_expression[i] == '-' && i == 0) {
				_expression[i] = '$';
				continue;
			}
			for (int i = 0; i < _expression.length(); i++) {
				if (_expression[i] == '-' && (i == 0 || operators.find(_expression[i - 1]) != std::string::npos))
					_expression[i] = '$';
			}
			std::string Digital_1, Digital_2;
			int j = i - 1, k = i + 1;
			while (isdigit(_expression[j]) || _expression[j] == '.') {
				Digital_1 += _expression[j];
				if (j == 0)
					break;
				j--;
			}
			for (int s = 0; s < Digital_1.length() / 2; s++)
				std::swap(Digital_1[s], Digital_1[Digital_1.length() - 1 - s]);
			if (_expression[j] == '$') {
				Digital_1.insert(0, 1, '-');
				j--;
			}
			if (_expression[i + 1] == '$') {
				Digital_2 = '-';
				k++;
			}
			while (isdigit(_expression[k])) {
				Digital_2 += _expression[k];
				if (k == _expression.length())
					break;
				k++;
			}
			double result = performOperation(std::stod(Digital_1), std::stod(Digital_2), _expression[i]);
			std::string _result = std::to_string(result);
			while (_result.back() == '0' || _result.back() == '.') {
				if (_result.back() == '.') {
					_result.erase(_result.length() - 1);
					break;
				}
				_result.erase(_result.length() - 1);
			}
			if (j == 0)
				_expression.replace(j, k - j, _result);
			else
				_expression.replace(j + 1, k - j - 1, _result);
			i = 0;
		}
	}
	return _expression;
}

std::string Bracket_Killer(std::string _equation) {
	std::string operators = "+-/*", close = "}])", open = "{[(", bracketed_expression = "", answer = "";
	int first = 0, second = 0;
	for (int i = 0; i < _equation.length(); i++) {
		if (open.find(_equation[i]) != std::string::npos) {
			bracketed_expression.clear();
			first = i;
			continue;
		}
		bracketed_expression += _equation[i];
		if (close.find(_equation[i]) != std::string::npos) {
			second = i;
			bracketed_expression.erase(bracketed_expression.length() - 1);
			answer = equals(bracketed_expression);
			_equation.replace(first, second - first + 1, answer);
			i = first = second = 0;
			bracketed_expression.clear();
		}
	}
	if (answer != _equation) {
		_equation.erase(_equation.length() - 1);
		answer = equals(_equation);
	}
	if (answer[0] == '$')
		answer[0] = '-';

	return answer;
}

bool IsWithoutMistake(const std::string tested) {
	std::string open = { '{','(','[' }, close = { '}',')',']' }, operators = { '-','+','/','*','=' };
	std::string bracket, withoutBr;

	int i = 0, count = 0;
	while (i < tested.length()) {
		if (tested[i] == ' ') {
			i++;
			continue;
		}
		if (open.find(tested[i]) != std::string::npos) {
			bracket += tested[i];
			if ((operators.find(tested[i + 1]) != std::string::npos) && tested[i + 1] != '-')
				return false;
			count++;
		}
		if ((bracket.length() != 0) && close.find(tested[i]) == open.find(bracket.back())) {
			bracket.pop_back();
			if (operators.find(tested[i - 1]) != std::string::npos)
				return false;
			count--;
		}
		if (operators.find(tested[i]) != std::string::npos) {
			if (operators.find(tested[i + 1]) != std::string::npos)
				return false;
			if (i == 0 && tested[i] != '-')
				return false;
			if (tested[i + 1] == '=' && (i + 1) != tested.length())
				return false;
		}
		i++;
	}
	if (bracket.length() == 0 && tested.back() == '=')
		return true;
	return false;
}

std::string calcualtion(std::string equation) {
	if (IsWithoutMistake(equation)) {
		std::string answer = Bracket_Killer(equation);
		return (answer);
	}
	else
		throw std::runtime_error("Error!");
}

int main() {
	std::string equation_1 = "(1+2*(3+4*(3-2*(4-2))))="; std::cout << equation_1 << calcualtion(equation_1) << std::endl;
	std::string equation = "((-28+34*2*5)*5*(-10)-1)="; std::cout << equation << calcualtion(equation) << std::endl;
	std::string equation_2 = "(8-5*(4/2))="; std::cout << equation_2 << calcualtion(equation_2) << std::endl;
	std::string equation_3 = "1+(9*((4*7/(-2))*(-1)))=";  std::cout << equation_3 << calcualtion(equation_3) << std::endl;
}