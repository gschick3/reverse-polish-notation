#include <iostream>
#include <vector>
#include <string>   // std::stod
#include <stdlib.h> // system
#include <math.h>   // pow

int factorial(int n);

int main()
{
	std::vector<double> stack;
	double last = 0;

	int window_height = 4;

	std::string in;

	while (true) {
		if (last == 0) last = 0; // prevent negative 0 display

		system("CLS");
		std::cout << "--------------" << std::endl;

		if ((int)stack.size() >= window_height) {
			for (int i = stack.size() - window_height; i < (int)stack.size(); i++)
				std::cout << "| " << stack.at(i) << std::endl;
		}
		else {
			for (int i = 0; i < window_height - stack.size(); i++)
				std::cout << '|' << std::endl;
			for (int n : stack)
				std::cout << "| " << n << std::endl;
		}
		std::cout << "|-------------\n" << "| " << last << std::endl;
		std::cout << "--------------" << std::endl;

		std::cout << "> ";
		std::cin >> in;
		std::cin.clear();

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
			else last = 0;
			break;

		case '/':
			if ((int)stack.size() > 0) {
				last = stack.back() / last;
				stack.pop_back();
			}
			else last = 0;
			break;

		case '^':
			if ((int)stack.size() > 0) {
				last = pow(stack.back(), last);
				stack.pop_back();
			}
			else last = 0;
			break;

		case '_':
			if ((int)stack.size() > 0) {
				last = pow(stack.back(), (1. / last));
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

		case 'q':
			return 0;

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
			if ((int)stack.size() > 0 || last != 0)
				stack.push_back(last);
			last = std::stod(in);
			break;
		}

	}
}

int factorial(int n) {
	int product = 1;
	for (n; n > 1; n--) {
		product *= n;
	}
	return product;
}