#include "BitcoinExchange.hpp"

bool isValidArgc(int &ac) 
{ 
	if (ac > 2 ) 
	{ 
		std::cerr << "args must 2 args\n"; 
		return false; 
	}
	if(ac == 1)
	{ 
		std::cerr << "Error: file input Not Found.\n";
		return false; 
	}
	return true; 
}

bool openFile(const char *nameFile, std::ifstream &fileOpen)
{
	fileOpen.open(nameFile);

	if (!fileOpen.is_open())
	{
		std::cerr << "Error: could not open file.\n";
		return false;
	}
	return true;
}

int main(int ac, char *av[])
{
	std::ifstream input;
	std::ifstream database;
	BitcoinExchange obj;

	if (!isValidArgc(ac) || !openFile("data.csv", database) || !openFile(av[1], input))
		return 1;
	obj.parseDB(database);
	obj.exchange(input);
	return 0;
}
