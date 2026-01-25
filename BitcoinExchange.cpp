#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

static void extractKeyValue(std::string& str, std::string& value, std::string& key)
{
	size_t index_pip = str.find(',');

	key = str.substr(0, index_pip);
	value = str.substr(index_pip + 1);
}

void BitcoinExchange::parseDB(std::ifstream& DB)
{
	std::string str;
	std::string key;
	std::string value;

	while (std::getline(DB, str))
	{
		extractKeyValue(str, value, key);
		database[key] = std::strtod(value.c_str(), NULL);
	}
}
// static void va(std::string& line)
// {

// }
void BitcoinExchange::exchange(std::ifstream& input)
{
	std::string line;
	int oneTime = 1;
	while (std::getline(input, line))
	{
		try{
			if (line == "date | value" && oneTime){
				oneTime = 0;
				continue;
			}
			size_t pos = line.find('|');
			if (pos == std::string::npos)
				throw std::runtime_error("Error: bad input => " + line);
			if (std::isspace(line[0]) || std::isspace(line[line.size() - 1]))
				throw std::runtime_error("Error: bad input (found space at first or end) => " + line);
		}
		catch(std::exception& e){
			std::cerr << e.what() << std::endl;
		}
		
	}
	
}
