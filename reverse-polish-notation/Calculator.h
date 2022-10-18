#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <math.h>

class Calculator
{
private:
	std::vector<double> stack;
	double lastInput;

	int resetWindowHeight;
	int currWindowHeight;

	int factorial(int);

public:
	Calculator();
	Calculator(int);
	bool input(std::string);
	void printScreen();
	void printHelp();
};