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