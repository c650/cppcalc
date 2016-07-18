#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <math.h>

#include "./evaluator.cpp"
#include "./parser.cpp"

int main() {
	/*
	    Take input from user...
	*/
	std::queue<char> operations;
	std::queue<double> operands;
	std::string str; getline(std::cin, str);
	parse_input(str, operations, operands);

	std::cout << evaluate(operations, operands) << std::endl;
	return 0;
}