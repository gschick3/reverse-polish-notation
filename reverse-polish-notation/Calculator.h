#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <string>
#include <math.h>

class Calculator
{
private:
	int factorial(int);

	int windowHeight;
	std::vector<double> stack;
	double last;


public:
	Calculator();
	Calculator(int);
	bool input(std::string);
	void printScreen();
	void printHelp();
};