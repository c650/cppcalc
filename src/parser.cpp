void parse_input(std::string& str, std::queue<char>& operations, std::queue<double>& operands) {
	
	str.erase(std::remove_if(str.begin(), str.end(), isspace)
			  , str.end()); // remove spaces
	

	/* STRING PARENTHESIS STUFF*/
	std::string::iterator it, it2;
	
	/* IF a ( is found...*/
	while ((it = std::find(str.begin(), str.end(), '(')) != str.end()) {

		unsigned int ign = 0;
		
		/*
			Traverse the rest of the string until that ( is closed with ).
			But we will make sure to account for nested ()...
		*/
		for (it2 = it+1; it2 != str.end(); it2++) {
			if (*it2 == '(') {
				ign++;
			} else if (*it2 == ')') {
				if (ign == 0) {
					break;
				} else {
					ign--;
				}
			}
		}

		std::string tmp(it + 1, it2);
		parse_input(tmp, operations, operands);

		//std::cout << "evaluating " << tmp << std::endl;
		tmp = std::to_string( evaluate(operations, operands) );
		//std::cout << "\tit became " << tmp << std::endl;

		str.erase(it,
				 (it2 == str.end() ? it2 : it2 + 1) );
				/*
					If we add 1 to str.end() in the case that it2 == str.end(),
					we SegFault, and nobody wants a SegFault.
				*/

		str.insert(it, tmp.begin(), tmp.end());

		operations = std::queue<char>();
		operands = std::queue<double>();
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