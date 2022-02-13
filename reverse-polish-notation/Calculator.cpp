#include "Calculator.h"
#include <iostream>

Calculator::Calculator() {
	windowHeight = 3;
	last = 0;
}

bool Calculator::input(std::string in) {
	switch (in.at(0)) {
	// Addition
	case '+':
		if ((int)stack.size() > 0) {
			last += stack.back();
			stack.pop_back();
		}
		break;

	// Multiplication
	case '*':
		if ((int)stack.size() > 0) {
			last *= stack.back();
			stack.pop_back();
		}
		break;

	// Division
	case '/':
		if ((int)stack.size() > 0) {
			last = stack.back() / last;
			stack.pop_back();
		}
		break;

	// Exponent
	case '^':
		if ((int)stack.size() > 0) {
			last = pow(stack.back(), last);
			stack.pop_back();
		}
		break;

	// Nth root
	case '_':
		if ((int)stack.size() > 0) {
			last = pow(stack.back(), (1 / last));
			stack.pop_back();
		}
		break;

	// Factorial
	case '!':
		last = factorial(last);
		break;

	// Percent
	case '%':
		last *= 100;
		break;

	// Logs
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

	// Pi
	case 'p':
		if (in == "pi") {
			if ((int)stack.size() > 0 || last != 0)
				stack.push_back(last);
			last = M_PI;
		}
		break;

	// Euler's Number
	case 'e':
		if ((int)stack.size() > 0 || last != 0)
			stack.push_back(last);
		last = M_E;
		break;

	// Delete last input
	case '<':
		if ((int)stack.size() > 0) {
			last = stack.back();
			stack.pop_back();
		}
		else last = 0;
		break;
	
	// Set window height
	case 'w':
		if (in.length() == 1)
			windowHeight = 3;																							// reset to default
		else if (in.at(1) == '+' && windowHeight < 8)
			windowHeight++;
		else if (in.at(1) == '-' && windowHeight > 1)
			windowHeight--;
		break;

	case '?':
		printHelp();
		break;

	case 'q':
	case 'x':
		return false;
	
	// Subtraction
	case '-':																											// fall through if input is a negative number
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
			double din = std::stod(in);																					// throws exception if in is anything other than number
			if ((int)stack.size() > 0 || last != 0)
				stack.push_back(last);
			last = din;
		}
		catch (std::invalid_argument& ia) {
			std::cout << ia.what() << std::endl;
		}
		break;
	}
	return true;
}

int Calculator::factorial(int n) {
	int product = 1;
	for (n; n > 1; n--)
		product *= n;
	return product;
}

void Calculator::printScreen() {
	if (last == 0) last = 0;																							// prevent negative 0 display
	system("CLS");
	std::cout << "? for help\n";
	std::cout << "--------------\n";

	for (int i = 0; i < (windowHeight >= stack.size() ? windowHeight - stack.size() : 0); i++)							// Print edge of display before numbers
		std::cout << '|' << std::endl;
	for (int i = (int)stack.size() >= windowHeight ? stack.size() - windowHeight : 0; i < (int)stack.size(); i++) {		// Print edge of display with numbers
		std::cout << "| ";
		if (stack.at(i) == M_PI) std::cout << "pi\n";
		else if (stack.at(i) == M_E) std::cout << "e\n";
		else std::cout << stack.at(i) << std::endl;
	}

	std::cout << "|-------------\n| ";
	if (last == M_PI) std::cout << "pi\n";
	else if (last == M_E) std::cout << "e\n";
	else std::cout << last << std::endl;
	std::cout << "--------------\n";

	std::cout << "> ";
}

void Calculator::printHelp() {
	system("CLS");
	std::cout << "Input one number or command at a time\n";
	std::cout << "Commands:\n\n";

	std::cout << "+\t- Add\n";
	std::cout << "-\t- Subtract\n";
	std::cout << "*\t- Multiply\n";
	std::cout << "/\t- Divide\n\n";

	std::cout << "^\t- Exponent\n";
	std::cout << "_\t- Root\n";
	std::cout << "log\t- Log base 10\n";
	std::cout << "ln\t- Log base e\n";
	std::cout << "logb\t- Log base b\n\n";

	std::cout << "!\t- Factorial\n";
	std::cout << "%\t- Percent\n\n";

	std::cout << "e\t- E\n";
	std::cout << "pi\t- PI\n\n";

	std::cout << "<\t- Backspace\n\n";

	std::cout << "w+\t- Increase window height\n";
	std::cout << "w-\t- Decrease window height\n";
	std::cout << "w\t- Reset window height to default (3)\n\n";

	std::cout << "x or q\t- Exit\n\n";

	char c = '\0';
	std::cout << "Type 'x' to exit help... ";
	while (tolower(c) != 'x')
		std::cin >> c;
}
