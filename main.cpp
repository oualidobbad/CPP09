#include "BitcoinExchange.hpp"

bool isValideArgc(int &ac)
{
	if (ac > 2 )
	{
		std::cerr << "args must 2 args\n";
		return false;
	}
	if(ac == 1)
	{
		std::cerr << "Error: could not open file.\n";
		return false;
	}
	return true;
}
int main (int ac, char *av[])
{

	
	return 0;
}