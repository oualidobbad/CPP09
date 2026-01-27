#pragma once

#include <iostream>
#include <vector>

typedef std::string String;

template <typename T>
struct Vector : public std::vector<T>{};

class RPN
{
	private:
		Vector<String> tokens;
		void checkAndCalculate();

	public:
		RPN();
		RPN(const RPN& other);
		RPN& operator=(const RPN& other);
		~RPN();
		void tokenizing(String arg);
		void print();
};


