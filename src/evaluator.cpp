static void scan_exponents(std::queue<char>& operations, std::queue<double>& operands) {

	std::queue<char> operations_dup;
	std::queue<double> operands_dup;

	double lhs; char op;

	while(!operations.empty()) {

		lhs = operands.front(); operands.pop();
		op = operations.front(); operations.pop();

		if (op == '^') {
			//std::cout << "lhs = " << lhs << " and rhs = " << operands.front() << std::endl;
			operands_dup.push(pow(lhs,operands.front()));
			operands.pop();
		} else {
			operands_dup.push(lhs);
			operations_dup.push(op);
		}
	}

	while(!operands.empty()) {
		operands_dup.push(operands.front());
		operands.pop();
	}

	operands = operands_dup;
	operations = operations_dup;
}

double evaluate(std::queue<char>& operations, std::queue<double>& operands) {
	
	/* Take care of exponents */
	scan_exponents(operations, operands);

	double lhs, rhs; char op;

	while(!operations.empty()) {

		lhs = operands.front(); operands.pop();
		/* rhs will stay `operands.front()`; do not pop this to save for next step */
		
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

	return operands.empty() ? lhs : operands.front();
}