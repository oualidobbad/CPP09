#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : struggle(-1), range(0), timeOfVector(0), timeOfDeque(0) {}
PmergeMe::PmergeMe(const PmergeMe &other) : struggle(other.struggle), range(other.range), timeOfVector(other.timeOfVector), timeOfDeque(other.timeOfDeque), vector_nb(other.vector_nb), deque_nb(other.deque_nb), numbersConverted(other.numbersConverted) {}

void PmergeMe::print()
{
	std::list<int>::iterator it = this->numbersConverted.begin();

	std::cout << "Before: ";
	for (; it != numbersConverted.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << std::fixed << std::setprecision(4);
	std::cout << "Time to process a range of " << range << " elements with std::deque<int> : " << timeOfDeque << " us\n";
	std::cout << "Time to process a range of " << range << " elements with std::vector<int> : " << timeOfVector << " us\n";
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
	if (&other != this)
	{
		struggle = other.struggle;
		range = other.range;
		vector_nb = other.vector_nb;
		deque_nb = other.deque_nb;
		numbersConverted = other.numbersConverted;
		timeOfDeque = other.timeOfDeque;
		timeOfVector = other.timeOfVector;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{
}

void PmergeMe::IsvalideArgs(char **argv, int ac)
{
	long number = 0;
	errno = 0;
	char *endConvertion;

	for (int i = 1; i < ac; i++)
	{
		number = std::strtol(argv[i], &endConvertion, 10);
		if (argv[i][0] == '-' || *endConvertion)
			throw std::runtime_error("Error: Invalide arg => " + static_cast<String>(argv[i]));
		if (errno == ERANGE || number > INT_MAX)
			throw std::runtime_error("Error: Overflow Number => " + static_cast<String>(argv[i]));
		numbersConverted.push_back(number);
	}
	range = ac - 1;
}

double getTime()
{
	struct timeval time;
	gettimeofday(&time, NULL);
	return time.tv_sec * 1000000.0 + time.tv_usec;
}

void swapNb(int &a, int &b)
{
	if (a < b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}
}

void insertionSortVector(std::vector<std::pair<int, int> > &pairs)
{
	std::pair<int, int> key;
	size_t i;
	ssize_t j;

	for (i = 1; i < pairs.size(); i++)
	{
		key = pairs[i];
		for (j = i - 1; j >= 0 && key.first < pairs[j].first; j--)
			pairs[j + 1] = pairs[j];
		pairs[j + 1] = key;
	}
}

void insertionSortDeque(std::deque<std::pair<int, int> > &pairs)
{
	std::pair<int, int> key;
	size_t i;
	ssize_t j;

	for (i = 1; i < pairs.size(); i++)
	{
		key = pairs[i];
		for (j = i - 1; j >= 0 && key.first < pairs[j].first; j--)
			pairs[j + 1] = pairs[j];
		pairs[j + 1] = key;
	}
}

void PmergeMe::sortingInDeque()
{
	double start;
	std::list<int>::iterator it;

	start = getTime();
	for (it = this->numbersConverted.begin(); it != numbersConverted.end(); it++)
		this->deque_nb.push_back(*it);
	pairSortElementDeque();
	this->timeOfDeque = getTime() - start;
}

void PmergeMe::sortingInVector()
{
	double start;
	std::list<int>::iterator it;

	start = getTime();
	for (it = this->numbersConverted.begin(); it != numbersConverted.end(); it++)
		this->vector_nb.push_back(*it);
	pairSortElementVector();
	this->timeOfVector = getTime() - start;
}

void PmergeMe::pairSortElementVector()
{
	std::vector<std::pair<int, int> > pairs;
	size_t i;

	// std::cout << "============= VECTOR =============\n";
	for (i = 0; i + 1 < vector_nb.size(); i += 2)
	{
		swapNb(vector_nb[i], vector_nb[i + 1]);
		pairs.push_back(std::make_pair(vector_nb[i], vector_nb[i + 1]));
	}
	if (i < vector_nb.size())
	{
		struggle = vector_nb[i];
	}
	insertionSortVector(pairs);
	// for (i = 0; i < pairs.size(); i++)
	// {
	// 	std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] ";
	// }
	// std::cout << "[" << struggle << "]";
	// std::cout << std::endl;
}

void PmergeMe::pairSortElementDeque()
{
	std::deque<std::pair<int, int> > pairs;
	size_t i;

	// std::cout << "============= DEQUE =============\n";
	for (i = 0; i + 1 < deque_nb.size(); i += 2)
	{
		swapNb(deque_nb[i], deque_nb[i + 1]);
		pairs.push_back(std::make_pair(deque_nb[i], deque_nb[i + 1]));
	}
	if (i < deque_nb.size())
	{
		struggle = deque_nb[i];
	}
	insertionSortDeque(pairs);
	// for (i = 0; i < pairs.size(); i++)
	// {
	// 	std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] ";
	// }
	// std::cout << "[" << struggle << "]";
	// std::cout << std::endl;
}
