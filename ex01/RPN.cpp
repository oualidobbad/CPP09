#include "RPN.hpp"

//=========== canonical orthodox ================
RPN::RPN() {}
RPN::RPN(const RPN& other) : tokens(other.tokens) {}

RPN& RPN::operator=(const RPN& other){
	if (&other != this)
		tokens = other.tokens;
	return *this;
}

RPN::~RPN(){}

void RPN::print()
{
	std::vector<std::string>::iterator it_b = tokens.begin();
	std::vector<std::string>::iterator it_e = tokens.end();

	for (; it_b != it_e; it_b++) {
		std::cout << "[" << *it_b << "]" << std::endl;
	}
}

void RPN::tokenizing(String line)
{
	size_t start = 0;
	std::string spaces = " \t\n\v\f\r";
	size_t end;
	String str;

	while ((end = line.find_first_of(spaces, start)) != std::string::npos)
	{
		str = line.substr(start, end - start);
		if (str.size() > 1)
			throw std::runtime_error("invalid input => " + str);
		if (!std::isspace(str[0]))
		{
			if (!std::isdigit(str[0]))
				throw std::runtime_error("invalid input => " + str);
			tokens.push_back(str);
		}
		start = end + 1;
	}
	if (start < line.size())
	{
		str = line.substr(start);
		if (str.size() > 1)
			throw std::runtime_error("invalid input => " + str);
		if (!std::isdigit(str[0]))
				throw std::runtime_error("invalid input => " + str);
		tokens.push_back(str);
	}


}



