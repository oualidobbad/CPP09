#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <cctype>

class BitcoinExchange
{
	private:
		std::map<std::string, double> database;
 
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange& operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void parseDB(std::ifstream& DB);
		void exchange(std::ifstream& input);
};
