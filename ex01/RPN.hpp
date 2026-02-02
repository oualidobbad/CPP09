#pragma once

#include <iostream>
#include <queue>
#include <stack>
#include <cstdlib>

typedef std::string String;

template <typename T>
struct Queue : public std::queue<T>{};

template <typename T>
struct Stack : public std::stack<T> {};

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
