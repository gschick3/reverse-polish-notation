#include <iostream>
#include "Calculator.h"

constexpr int WINDOW_HEIGHT = 3;

int main()
{
	Calculator calc;
	std::string in;
	bool run = true;

	while (run) {

		calc.printScreen();

		std::cin >> in;
		std::cin.clear();

		run = calc.input(in);
	}
}