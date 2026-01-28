#include "RPN.hpp"

//=========== canonical orthodox ================
RPN::RPN() {}
RPN::RPN(const RPN &other) : tokens(other.tokens) {}

RPN &RPN::operator=(const RPN &other)
{
	if (&other != this)
		tokens = other.tokens;
	return *this;
}

RPN::~RPN() {}

bool RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '/' || c == '*');
}

void RPN::parse_calculate(String line)
{
	size_t start = 0;
	String spaces = " \t\n\v\f\r";
	size_t end;
	String str;

	line += " ";
	while ((end = line.find_first_of(spaces, start)) != std::string::npos)
	{
		str = line.substr(start, end - start);
		if (str.size() > 1)
			throw std::runtime_error("invalid input => " + str);
		if (!std::isspace(str[0]) && str[0])
		{
			if (!std::isdigit(str[0]) && !isOperator(str[0]))
				throw std::runtime_error("invalid input => " + str);
			tokens.push(str);
		}
		start = end + 1;
	}
	Calculate();
}
static int CalculateOperation(char c, int &a, int &b)
{
	switch (c)
	{
	case '+':
		return a + b;
	case '*':
		return a * b;
	case '-':
		return a - b;
	case '/':
		return a / b;
	default:
		return 0;
	}
}
// 1 + 2
// 1 2 +

static bool isNumber(String str)
{
	for (String::iterator it = str.begin(); it != str.end(); it++)
	{
		if (std::isdigit(*it))
			return true;
	}
	return false;
}

void RPN::Calculate()
{
	Stack<int> stack;
	String tok;
	int result;
	int a;
	int b;

	while (!tokens.empty())
	{
		tok = tokens.front();
		tokens.pop();

		if (isNumber(tok))
			stack.push(std::strtol(tok.c_str(), NULL, 10));
		else if (isOperator(tok[0]))
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error: Bad input => " + tok);

			b = stack.top();
			stack.pop();
			a = stack.top();
			stack.pop();
			result = CalculateOperation(tok[0], a, b);
			stack.push(result);
		}
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error: Bad input");
	std::cout << stack.top() << std::endl;
}
