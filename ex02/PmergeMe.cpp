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

std::vector<std::pair<int, int> > fordJhonson(std::vector<std::pair<int, int> > pairs)
{	std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > MetaPair;

	if (pairs.size() <= 1)
		return pairs;
	
}

void PmergeMe::pairSortElementVector()
{
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> lowest;
	std::vector<int> largest;
	std::vector<int>::iterator it;


	std::cout << "============= VECTOR =============\n";
	for (it = vector_nb.begin(); it + 1 < vector_nb.end(); it += 2)
	{
		if (*it < *(it + 1))
			std::swap(*it, *(it + 1));
		pairs.push_back(std::make_pair(*it, *(it+1)));
	}

	if (vector_nb.size() % 2)
		struggle = *(vector_nb.end() - 1);
	sort(pairs.begin(), pairs.end());
	
	// for (size_t i = 0; i < pairs.size(); i++)
	// {
	// 	std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] ";
	// }
	// std::cout << "[" << struggle << "]";
	// std::cout << std::endl;
}

// void PmergeMe::sortingInDeque()
// {
// 	double start;
// 	std::list<int>::iterator it;

// 	start = getTime();
// 	for (it = this->numbersConverted.begin(); it != numbersConverted.end(); it++)
// 		this->deque_nb.push_back(*it);
// 	pairSortElementDeque();
// 	this->timeOfDeque = getTime() - start;
// }

// void PmergeMe::pairSortElementDeque()
// {
// 	std::deque<std::pair<int, int> > pairs;
// 	std::deque<int>::iterator it;

// 	std::cout << "============= DEQUE =============\n";
// 	for (it = deque_nb.begin(); it + 1 < deque_nb.end(); it += 2)
// 	{
// 		sort(it , it + 2, std::greater<int>());
// 		pairs.push_back(std::make_pair(*it, *(it + 1)));
// 	}
// 	if (deque_nb.size() % 2)
// 		struggle = *(deque_nb.end() - 1);

// 	sort(pairs.begin(), pairs.end());
// 	// for (size_t i = 0; i < pairs.size(); i++)
// 	// {
// 	// 	std::cout << "[" << pairs[i].first << "," << pairs[i].second << "] ";
// 	// }
// 	// std::cout << "[" << struggle << "]";
// 	// std::cout << std::endl;
// }
