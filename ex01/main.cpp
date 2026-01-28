#include "RPN.hpp"

int main(int ac, char **av)
{
	try
	{
		RPN rpn;
		if (ac != 2)
			throw std::runtime_error("you must have 2 args");
		rpn.parse_calculate(av[1]);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}