#include "Calculator.h"
#include <iostream>

Calculator::Calculator(int windowHeight) {
	this->windowHeight = windowHeight;
	last = 0;
}

bool Calculator::input(std::string in) {
	switch (in.at(0)) {
	case '+':
		if ((int)stack.size() > 0) {
			last += stack.back();
			stack.pop_back();
		}
		break;

	case '*':
		if ((int)stack.size() > 0) {
			last *= stack.back();
			stack.pop_back();
		}
		break;

	case '/':
		if ((int)stack.size() > 0) {
			last = stack.back() / last;
			stack.pop_back();
		}
		break;

	case '^':
		if ((int)stack.size() > 0) {
			last = pow(stack.back(), last);
			stack.pop_back();
		}
		break;

	case '_':
		if ((int)stack.size() > 0) {
			last = pow(stack.back(), (1 / last));
			stack.pop_back();
		}
		break;

	case '<':
		if ((int)stack.size() > 0) {
			last = stack.back();
			stack.pop_back();
		}
		else last = 0;
		break;

	case '!':
		last = factorial(last);
		break;

	case '%':
		last *= 100;
		break;

	case 'p':
		if (in == "pi") {
			if ((int)stack.size() > 0 || last != 0)
				stack.push_back(last);
			last = M_PI;
		}
		break;

	case 'e':
		if ((int)stack.size() > 0 || last != 0)
			stack.push_back(last);
		last = M_E;
		break;

	case 'l':
		if (in == "logb") {
			if ((int)stack.size() > 0) {
				last = log(stack.back()) / log(last);
				stack.pop_back();
			}
		}
		else if (in == "log") {
			if (last > 0)
				last = log(last);
		}
		else if (in == "ln") {
			if (last > 0)
				last = log(last) / log(M_E);
		}
		break;

	case 'q':
	case 'x':
		return false;

	// place this case here so it can fall through to the default case
	case '-':
		if (in.size() == 1) {
			if ((int)stack.size() > 0) {
				last = stack.back() - last;
				stack.pop_back();
			}
			else last = 0 - last;
			break;
		}

	default:
		try {
			double din = std::stod(in); // throws exception if in is anything other than number
			if ((int)stack.size() > 0 || last != 0)
				stack.push_back(last);
			last = std::stod(in);
		}
		catch (std::invalid_argument& ia) {
			std::cout << ia.what() << std::endl;
		}
		break;
	}
	return true;
}

void Calculator::printScreen() {
	if (last == 0) last = 0; // prevent negative 0 display
	system("CLS");
	std::cout << "--------------" << std::endl;

	for (int i = 0; i < (windowHeight >= stack.size() ? windowHeight - stack.size() : 0); i++)
		std::cout << '|' << std::endl;
	for (int i = (int)stack.size() >= windowHeight ? stack.size() - windowHeight : 0; i < (int)stack.size(); i++) {
		std::cout << "| ";
		if (stack.at(i) == M_PI) std::cout << "pi" << std::endl;
		else if (stack.at(i) == M_E) std::cout << "e" << std::endl;
		else std::cout << stack.at(i) << std::endl;
	}

	std::cout << "|-------------\n| ";
	if (last == M_PI) std::cout << "pi" << std::endl;
	else if (last == M_E) std::cout << "e" << std::endl;
	else std::cout << last << std::endl;
	std::cout << "--------------" << std::endl;

	std::cout << "> ";
}

int Calculator::factorial(int n) {
	int product = 1;
	for (n; n > 1; n--)
		product *= n;
	return product;
}