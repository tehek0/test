#include <iostream>
#include <string>

struct value {
	double val;
	bool is_undefined = true;
	virtual double eval() {
		return val;
	}
	value() = default;
	value(double val_) {
		// std::cout << "new val: " << val_ << "\n";
		is_undefined = false;
		val = val_;
	}
	virtual ~value() = default;
};

struct expression : public value {
	value* val1 = nullptr;
	value* val2 = nullptr;
	char op;
	double eval() override {
		if (is_undefined != true)
			return val;

		if (val1 == nullptr || val2 == nullptr)
			return 0;

		double first = val1->eval();
		double second = val2->eval();
		if (val1->is_undefined || val2->is_undefined) 
			return 0;
		switch (op) {
			case '/': {
				if (second == 0) {
					return 0;
				}
				val = first / second;
				is_undefined = false;
				return val;
			}
			case '*': {
				val = first * second;
				is_undefined = false;
				return val;
			}
			case '+': {
				val = first + second;
				is_undefined = false;
				return val;
			}
			case '-': {
				val = first - second;
				is_undefined = false;
				return val;
			}
		}
	}
	~expression() {
		delete val1;
		delete val2;
	}
	expression() = default;
	expression(value* val1_, value* val2_, char op_) {
		set_values(val1_, val2_, op_);
		// std::cout << "new expr: " << val1_->eval() << " " << op_ << " " << val2_->eval() << "\n";
	}
	void set_values(value* val1_, value* val2_, char op_) {
		delete val1;
		delete val2;
		val1 = val1_;
		val2 = val2_;
		op = op_;
	}
};

value* get_first_expression(std::string& str, int& pos);

value* parse(std::string& str, int& start, value* inherit_expr = nullptr) {
	std::string num = "";
	while (start < str.size()) {
		char symbol = str[start];
		if (symbol == '(') {
			inherit_expr = get_first_expression(str, start);
			++start;
			symbol = str[start];
		}
		if (symbol == '*' || symbol == '/') {
			start++;
			if (inherit_expr == nullptr) {
				inherit_expr = new expression(new value(std::stod(num)), get_first_expression(str, start), symbol);
			}
			else {
				inherit_expr = new expression(inherit_expr, get_first_expression(str, start), symbol);
			}
			symbol = str[start];
			if (symbol == '*' || symbol == '/')
				continue;
		}
		if (symbol == '+' || symbol == '-') {
			++start;
			if (inherit_expr == nullptr) {
				return new expression(new value(std::stod(num)), parse(str, start), symbol);
			}
			return new expression(inherit_expr, parse(str, start), symbol);
		}
		if (symbol == '=' || symbol == ')') {
			++start;
			if (inherit_expr != nullptr)
				return inherit_expr;
			
			return new value(std::stod(num));
		}
		num += symbol;
		start++;
	}
}

value* parse_mod(std::string& str, int& start, value* inherit_expr = nullptr) {
	return parse(str, start, nullptr);
}

value* get_first_expression(std::string& str, int& pos) {
	std::string num = "";
	while (pos < str.size()) {
		char symbol = str[pos];
		if ((symbol < '0' || symbol > '9') && symbol != '.') {
			if (symbol == '(') {
				++pos;
				return parse(str, pos);
			}
			return new value(std::stod(num));
		}
		num += symbol;
		pos++;
	}
}

int validate(std::string& str, int pos = 0) {
	while (true) {
		pos++;
		if (pos >= str.size())
			return -1;
		char symbol = str[pos];
		if (symbol == ')') {
			return pos;
		}
		if (symbol == '(') {
			int result = validate(str, pos);
			if (result == -1)
				return -1;

			pos = result;
		}
	}
}

int main() {
	std::setlocale(LC_ALL, "Russian");

	std::string input;
	std::cin >> input;

	std::string extra_input = "(";
	extra_input += input;
	extra_input += ")";

	if (validate(extra_input) == -1) {
		std::cout << "Некорректные скобки";
		return 0;
	}


	int start = 0;
	expression* result = reinterpret_cast<expression*>(parse(input, start));
	double num = result->eval();
	if (result->is_undefined) {
		std::cout << "Не определено ";
		delete result;
		return 0;
	}
	std::cout << num;
	delete result;

}