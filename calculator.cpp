#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>

void take_input(std::queue<char>& operations, std::queue<double>& operands);
double evaluate(std::queue<char>& operations, std::queue<double>& operands);

int main() {
	/*
	    Take input from user...
	*/
	std::queue<char> operations;
	std::queue<double> operands;
	take_input(operations, operands);

	std::cout << evaluate(operations, operands) << std::endl;
	return 0;
}

void take_input(std::queue<char>& operations, std::queue<double>& operands) {
	std::string str;
	std::getline(std::cin, str);
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end()); // remove spaces
	std::stringstream expression(str);

	char c; double d;
	while(expression >> d  >> c) {	
		operands.push(d);
		operations.push(c);
	}
	expression >> d;
	operands.push(d);
}

double evaluate(std::queue<char>& operations, std::queue<double>& operands) {
	double lhs, rhs; char op;

	while(!operations.empty()) {

		lhs = operands.front(); operands.pop();
		// rhs will stay `operands.front()`; do not pop this to save for next step
		op = operations.front(); operations.pop();

		while(operations.front() == '*' || operations.front() == '/') {
			rhs = operands.front(); operands.pop();

			if (operations.front() == '*') {
				operands.front() *= rhs;
			}
			else if (operations.front() == '/') {
				operands.front() = rhs / operands.front();
			}

			operations.pop();
		}

		switch (op) {
			case '+':
				operands.front() += lhs;
				break;
			case '-':
				operands.front() = lhs - operands.front();
				break;
			case '*':
				operands.front() *= lhs;
				break;
			case '/':
				operands.front() = lhs / operands.front();
				break;
		}
	}

	return operands.front();
}





