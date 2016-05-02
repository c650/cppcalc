#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>

void parse_input(std::string& str, std::queue<char>& operations, std::queue<double>& operands);
double evaluate(std::queue<char>& operations, std::queue<double>& operands);

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

void parse_input(std::string& str, std::queue<char>& operations, std::queue<double>& operands) {
	
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end()); // remove spaces
	// string parenthesis stuff
	std::string::iterator it, it2;
	it = std::find(str.begin(), str.end(), '(');
	
	while ( it != str.end() ) {
		it2 = std::find(str.begin(), str.end(), ')');
		// may be an error here
		std::string tmp(it + 1, it2 - 1);
		parse_input(tmp, operations, operands);

		tmp = std::to_string( evaluate(operations, operands) );
		str.erase(it, it2 + 1);
		str.insert(it, tmp.begin(), tmp.end());

		operations = std::queue<char>();
		operands = std::queue<double>();

		it = std::find(str.begin(), str.end(), '(');
	}

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