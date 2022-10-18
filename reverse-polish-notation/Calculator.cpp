#include "Calculator.h"
#include <iostream>

using namespace std;

Calculator::Calculator() {
	currWindowHeight = 3;
	resetWindowHeight = 3;
	lastInput = 0;
}
Calculator::Calculator(int windowHeight) {
	currWindowHeight = windowHeight;
	resetWindowHeight = windowHeight;
	lastInput = 0;
}

bool Calculator::input(string in) {
	switch (in.at(0)) {
	// Addition
	case '+':
		if (static_cast<int>(stack.size()) > 0) {
			lastInput += stack.back();
			stack.pop_back();
		}
		break;

	// Multiplication
	case '*':
		if (static_cast<int>(stack.size()) > 0) {
			lastInput *= stack.back();
			stack.pop_back();
		}
		break;

	// Division
	case '/':
		if (static_cast<int>(stack.size()) > 0) {
			lastInput = stack.back() / lastInput;
			stack.pop_back();
		}
		break;

	// Exponent
	case '^':
		if (static_cast<int>(stack.size()) > 0) {
			lastInput = pow(stack.back(), lastInput);
			stack.pop_back();
		}
		break;

	// Nth root
	case '_':
		if (static_cast<int>(stack.size()) > 0) {
			lastInput = pow(stack.back(), (1 / lastInput));
			stack.pop_back();
		}
		break;

	// Factorial
	case '!':
		lastInput = factorial(lastInput);
		break;

	// Percent
	case '%':
		lastInput *= 100;
		break;

	// Logs
	case 'l':
		if (in == "logb") {
			if (static_cast<int>(stack.size()) > 0) {
				lastInput = log(stack.back()) / log(lastInput);
				stack.pop_back();
			}
		}
		else if (in == "log") {
			if (lastInput > 0)
				lastInput = log(lastInput);
		}
		else if (in == "ln") {
			if (lastInput > 0)
				lastInput = log(lastInput) / log(M_E);
		}
		break;

	// Pi
	case 'p':
		if (in == "pi") {
			if (static_cast<int>(stack.size()) > 0 || lastInput != 0)
				stack.push_back(lastInput);
			lastInput = M_PI;
		}
		break;

	// Euler's Number
	case 'e':
		if (static_cast<int>(stack.size()) > 0 || lastInput != 0)
			stack.push_back(lastInput);
		lastInput = M_E;
		break;

	// Delete last input
	case '<':
		if (static_cast<int>(stack.size()) > 0) {
			lastInput = stack.back();
			stack.pop_back();
		}
		else lastInput = 0;
		break;
	
	// Set window height
	case 'w':
		if (in.length() == 1)
			currWindowHeight = resetWindowHeight;			// reset to default
		else if (in.at(1) == '+' && currWindowHeight < 8)
			currWindowHeight++;
		else if (in.at(1) == '-' && currWindowHeight > 1)
			currWindowHeight--;
		break;

	case '?':
		printHelp();
		break;

	case 'q':
	case 'x':
		return false;
	
	// Subtraction
	case '-':												// fall through if input is a negative number
		if (in.size() == 1) {
			if (static_cast<int>(stack.size()) > 0) {
				lastInput = stack.back() - lastInput;
				stack.pop_back();
			}
			else lastInput = 0 - lastInput;
			break;
		}

	default:
		if (in.find_first_not_of("0123456789.-") != string::npos) break;
		double din = stod(in);
		if (static_cast<int>(stack.size()) > 0 || lastInput != 0)
			stack.push_back(lastInput);
		lastInput = din;
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
	if (lastInput == 0) lastInput = 0;						// prevent negative 0 display
	system("CLS");
	cout << "? for help\n";
	cout << "--------------\n";

	for (int i = 0; i < (currWindowHeight >= stack.size() ? currWindowHeight - stack.size() : 0); i++)
		cout << '|' << endl;								// Print edge of display before numbers

	for (int i = static_cast<int>(stack.size()) >= currWindowHeight ? stack.size() - currWindowHeight : 0; i < static_cast<int>(stack.size()); i++) {
		cout << "| ";										// Print edge of display with numbers
		if (stack.at(i) == M_PI) cout << "pi\n";
		else if (stack.at(i) == M_E) cout << "e\n";
		else cout << stack.at(i) << endl;
	}

	cout << "|-------------\n| ";
	if (lastInput == M_PI) cout << "pi\n";
	else if (lastInput == M_E) cout << "e\n";
	else cout << lastInput << endl;
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
