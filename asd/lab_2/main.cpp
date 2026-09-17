#include <iostream>
#include <string>
#include <vector>

struct value {
	double val;
	bool is_undefined = true;
	virtual double eval() {
		return val;
	}
	value() = default;
	value(double val_) {
		std::cout << "new val: " << val_ << "\n";
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
		std::cout << "new expr: " << val1_->eval() << " " << op_ << " " << val2_->eval() << "\n";
	}
	void set_values(value* val1_, value* val2_, char op_) {
		delete val1;
		delete val2;
		val1 = val1_;
		val2 = val2_;
		op = op_;
	}
};

value* parse(std::string& str, int start = 0) {
	std::string num = "";
	while (start < str.size()) {
		char symbol = str[start];
		if (symbol == '(') {
			if (!(num.size() == 0))
				return nullptr;
		}
		if (symbol == '+' || symbol == '-' || symbol == '/' || symbol == '*') {
			if (num.size() == 0) {
				return nullptr;
			}
			return new expression(new value(std::stod(num)), parse(str, start + 1), symbol);
		}
		if (symbol == '=' || symbol == ')') {
			if (num.empty())
				return nullptr;
			return new value(std::stod(num));
		}
		num += symbol;
		start++;
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

	expression* result = reinterpret_cast<expression*>(parse(input));
	double num = result->eval();
	if (result->is_undefined) {
		std::cout << "Не определено " << num;
		delete result;
		return 0;
	}
	std::cout << num;
	delete result;

}