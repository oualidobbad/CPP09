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

static void isValidDate(std::string& line)
{
	std::map<int, std::string> mapDate;
	int indexOfMap = 0;
	size_t pos = 0;
	size_t index;
	std::string date = line.substr(0, line.find('|') - 1);

	if (date.find(' ') != std::string::npos)
		throw std::runtime_error("Error: extra space in date => " + line);
	while ((index = date.find('-', pos)) != std::string::npos)
	{
		mapDate[indexOfMap] = date.substr(pos, index - pos);
		pos = ++index;
		indexOfMap++;
	}
	mapDate[indexOfMap] = date.substr(pos);
	if (indexOfMap != 2 || mapDate[indexOfMap].empty())
		throw std::runtime_error("Error: bad input => " + line);
	
	long month =  std::strtol(mapDate[1].c_str(), NULL, 10);
	long day =  std::strtol(mapDate[2].c_str(), NULL, 10);
	errno = 0;
	if (errno == ERANGE || month > 12 || day > 30)
		throw std::runtime_error("Error: invalid date => " + date);

}

static void calculateCurrency(std::string& line, std::map<std::string, double>& dataBase)
{
	std::string date = line.substr(0, line.find('|') - 1);
	std::string valueStr = line.substr(line.find('|') + 2);
	double value;
	char *endConversion;

	errno = 0;
	if (valueStr.find(' ') != std::string::npos)
		throw std::runtime_error("Error: extra space in value => " + line);
	value = std::strtod(valueStr.c_str(), &endConversion);

	if (errno == ERANGE || value > 1000 || value < 0)
	{
		
	}
	// std::cout << value << std::endl;
}

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
			isValidDate(line);
			calculateCurrency(line, this->database);
		}
		catch(std::exception& e){
			std::cerr << e.what() << std::endl;
		}
		
	}
	
}
