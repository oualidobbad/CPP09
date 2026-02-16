#include "PmergeMe.hpp"

int main(int ac, char *argv[])
{
	if (ac < 2)
		return 1;
	try
	{
		PmergeMe merge;

		merge.IsvalideArgs(argv, ac);
		merge.sortingInVector();
		merge.sortingInDeque();
		merge.print();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
}