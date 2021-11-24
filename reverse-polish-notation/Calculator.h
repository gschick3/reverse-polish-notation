#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <string>
#include <math.h>

class Calculator
{
private:
	int factorial(int n);

	int windowHeight;
	std::vector<double> stack;
	double last;


public:
	Calculator();
	bool input(std::string in);
	void printScreen();
	void printHelp();
};

