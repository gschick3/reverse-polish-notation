#include "Calculator.h"
#include <iostream>

using namespace std;

Calculator::Calculator() {
	windowHeight = 3;
	last = 0;
}
Calculator::Calculator(int windowHeight) {
	this->windowHeight = windowHeight;
	last = 0;
}

bool Calculator::input(string in) {
	switch (in.at(0)) {
	// Addition
	case '+':
		if (static_cast<int>(stack.size()) > 0) {
			last += stack.back();
			stack.pop_back();
		}
		break;

	// Multiplication
	case '*':
		if (static_cast<int>(stack.size()) > 0) {
			last *= stack.back();
			stack.pop_back();
		}
		break;

	// Division
	case '/':
		if (static_cast<int>(stack.size()) > 0) {
			last = stack.back() / last;
			stack.pop_back();
		}
		break;

	// Exponent
	case '^':
		if (static_cast<int>(stack.size()) > 0) {
			last = pow(stack.back(), last);
			stack.pop_back();
		}
		break;

	// Nth root
	case '_':
		if (static_cast<int>(stack.size()) > 0) {
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
			if (static_cast<int>(stack.size()) > 0) {
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
			if (static_cast<int>(stack.size()) > 0 || last != 0)
				stack.push_back(last);
			last = M_PI;
		}
		break;

	// Euler's Number
	case 'e':
		if (static_cast<int>(stack.size()) > 0 || last != 0)
			stack.push_back(last);
		last = M_E;
		break;

	// Delete last input
	case '<':
		if (static_cast<int>(stack.size()) > 0) {
			last = stack.back();
			stack.pop_back();
		}
		else last = 0;
		break;
	
	// Set window height
	case 'w':
		if (in.length() == 1)
			windowHeight = 3;												// reset to default
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
	case '-':																// fall through if input is a negative number
		if (in.size() == 1) {
			if (static_cast<int>(stack.size()) > 0) {
				last = stack.back() - last;
				stack.pop_back();
			}
			else last = 0 - last;
			break;
		}

	default:
		try {
			double din = stod(in);											// throws exception if in is anything other than number
			if (static_cast<int>(stack.size()) > 0 || last != 0)
				stack.push_back(last);
			last = din;
		}
		catch (invalid_argument& ia) {
			cout << ia.what() << endl;
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
	if (last == 0) last = 0;												// prevent negative 0 display
	system("CLS");
	cout << "? for help\n";
	cout << "--------------\n";

	for (int i = 0; i < (windowHeight >= stack.size() ? windowHeight - stack.size() : 0); i++)
		cout << '|' << endl;												// Print edge of display before numbers

	for (int i = static_cast<int>(stack.size()) >= windowHeight ? stack.size() - windowHeight : 0; i < static_cast<int>(stack.size()); i++) {
		cout << "| ";														// Print edge of display with numbers
		if (stack.at(i) == M_PI) cout << "pi\n";
		else if (stack.at(i) == M_E) cout << "e\n";
		else cout << stack.at(i) << endl;
	}

	cout << "|-------------\n| ";
	if (last == M_PI) cout << "pi\n";
	else if (last == M_E) cout << "e\n";
	else cout << last << endl;
	cout << "--------------\n";

	cout << "> ";
}

void Calculator::printHelp() {
	system("CLS");
	cout << "Input one number or command at a time\n";
	cout << "Commands:\n\n";

	cout << "+\t- Add\n";
	cout << "-\t- Subtract\n";
	cout << "*\t- Multiply\n";
	cout << "/\t- Divide\n\n";

	cout << "^\t- Exponent\n";
	cout << "_\t- Root\n";
	cout << "log\t- Log base 10\n";
	cout << "ln\t- Log base e\n";
	cout << "logb\t- Log base b\n\n";

	cout << "!\t- Factorial\n";
	cout << "%\t- Percent\n\n";

	cout << "e\t- E\n";
	cout << "pi\t- PI\n\n";

	cout << "<\t- Backspace\n\n";

	cout << "w+\t- Increase window height\n";
	cout << "w-\t- Decrease window height\n";
	cout << "w\t- Reset window height to default (3)\n\n";

	cout << "x or q\t- Exit\n\n";

	char c = '\0';
	cout << "Type 'x' to exit help... ";
	while (tolower(c) != 'x')
		cin >> c;
}
