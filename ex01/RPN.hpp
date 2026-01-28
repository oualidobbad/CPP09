#pragma once

#include <iostream>
#include <queue>
#include <stack>

typedef std::string String;
typedef std::stack<int> StackInt;

template <typename T>
struct Queue : public std::queue<T>
{
};

class RPN
{
private:
	Queue<String> tokens;
	void Calculate();
	bool isOperator(char c);

public:
	RPN();
	RPN(const RPN &other);
	RPN &operator=(const RPN &other);
	~RPN();
	void parse_calculate(String arg);
};
