#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): database(other.database)
{
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other) {
        database = other.database;
    }
    return *this;
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

static long convertToNumber(const char* date, std::string& line)
{
	char *endConvertion;
	long value = std::strtol(date, &endConvertion, 10);

	errno = 0;
	if (*endConvertion != '\0' || errno == ERANGE)
		throw std::runtime_error("Error: bad input =>" + line);
	return value;
}

static void isValidDate(std::string& line)
{
	std::map<int, std::string> mapDate;
	int indexOfMap = 0;
	size_t pos = 0;
	size_t index;
	std::string date = line.substr(0, line.find('|') - 1);

	if (date.find(' ') != std::string::npos)
		throw std::runtime_error("Error: Invalid format. Expected format: [date␣|␣value] => " + line);
	while ((index = date.find('-', pos)) != std::string::npos)
	{
		mapDate[indexOfMap] = date.substr(pos, index - pos);
		pos = ++index;
		indexOfMap++;
	}
	mapDate[indexOfMap] = date.substr(pos);
	if (indexOfMap != 2 || mapDate[indexOfMap].empty())
		throw std::runtime_error("Error: bad input => " + line);
	
	int i = 0;
	while (i <= indexOfMap)
	{
		long number = convertToNumber(mapDate[i].c_str(), line);
		if (i == 1 && (number > 12 || number < 1))
			throw std::runtime_error("Error: bad input => " + line);
		if (i == 2 && (number > 30 || number < 1))
			throw std::runtime_error("Error: bad input => " + line);
		i++;
	}
}

static void calculateCurrency(std::string& line, std::map<std::string, double>& dataBase)
{
	std::string date = line.substr(0, line.find('|') - 1);
	std::string valueStr = line.substr(line.find('|') + 1);
	std::map<std::string, double>::iterator it;
	double value;
	char *endConversion;

	errno = 0;
	if (valueStr[0] != ' ')
		throw std::runtime_error("Error: Invalid format. Expected format: [date␣|␣value] => " + line);
	valueStr = valueStr.substr(1);
	if (valueStr.find(' ') != std::string::npos)
		throw std::runtime_error("Error: Invalid format. Expected format: [date␣|␣value] => " + line);
	value = std::strtod(valueStr.c_str(), &endConversion);
	if (*endConversion != '\0')
		throw std::runtime_error("Error: value not pure number.");
	if (value < 0 || (errno == ERANGE && valueStr[0] == '-'))
		throw std::out_of_range("Error: not a positive number.");
	if (errno == ERANGE || value > 1000)
		throw std::out_of_range("Error: too large a number.");
	it = dataBase.upper_bound(date);
	it--;
	std::cout << date + " => " + valueStr +" = " << it->second * value << std::endl;
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
				throw std::runtime_error("Error: Invalid format. Expected format: [date␣|␣value] => " + line);
			isValidDate(line);
			calculateCurrency(line, this->database);
		}
		catch(std::exception& e){
			std::cerr << e.what() << std::endl;
		}
		
	}
	
}
