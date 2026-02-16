#include "PmergeMe.hpp"

PmergeMe::PmergeMe() : struggle(-1), range(0), timeOfVector(0), timeOfDeque(0) {}
PmergeMe::PmergeMe(const PmergeMe &other) : struggle(other.struggle), range(other.range), timeOfVector(other.timeOfVector), timeOfDeque(other.timeOfDeque), vector_nb(other.vector_nb), deque_nb(other.deque_nb), numbersConverted(other.numbersConverted) {}

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

PmergeMe::~PmergeMe() {}

void PmergeMe::print()
{
	std::list<int>::iterator it = this->numbersConverted.begin();

	std::cout << "Before: ";
	for (; it != numbersConverted.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::cout << "After: ";
	for (size_t i = 0; i < vector_nb.size(); i++)
		std::cout << vector_nb[i] << " ";
	std::cout << std::endl;
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Time to process a range of " << range << " elements with std::deque<int> : " << timeOfDeque << " us\n";
	std::cout << "Time to process a range of " << range << " elements with std::vector<int> : " << timeOfVector << " us\n";
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
	return time.tv_sec * 1000000.0 + time.tv_usec ;
}

// ======================= Sort Vector =========================

void generateJacobsthalSequence(int size, std::vector<int>& jacobWithAllIdx)
{

	std::vector<int> jacob;
	int n;
	int min;
	int max;
	int i;

	jacob.push_back(0);
	jacob.push_back(1);
	n = 2;
	i = 0;
	while (*(jacob.end() - 1) < size)
	{
		jacob.push_back(jacob[n - 1] + 2 * jacob[n - 2]);
		n++;
	}
	jacob.erase(jacob.begin(), jacob.begin() + 2);
	i = 0;
	while (true)
	{
		max = jacob[i + 1];
		for (min = jacob[i]; max > min; max--)
			if (max <= size)
				jacobWithAllIdx.push_back(max - 1);
		if (min == jacob[jacob.size() - 2])
			break;
		i++;
	}
}

void PmergeMe::FordJhonsonVector(std::vector<int> &lowest, std::vector<int> &largest)
{
	std::vector<int> jacobSeq;
	std::vector<int>::iterator lb;
	int val;

	if (lowest.size() >= 1)
		largest.insert(largest.begin(), lowest[0]);
	if (lowest.size() <= 1)
		goto end;
	generateJacobsthalSequence(lowest.size(), jacobSeq);
	for (size_t i = 0; i < jacobSeq.size(); i++)
	{
		val = lowest[jacobSeq[i]];
		lb = std::lower_bound(largest.begin(), largest.end(), val);
		largest.insert(lb, val);
	}
	end:
		if (this->struggle != -1)
		{
			lb = std::lower_bound(largest.begin(), largest.end(), struggle);
			largest.insert(lb, struggle);
		}
		vector_nb = largest;
}

void PmergeMe::applyFordJhonsonVec()
{
	std::vector<std::pair<int, int> > pairs;
	std::vector<int> lowest;
	std::vector<int> largest;
	std::vector<int>::iterator it;

	for (it = vector_nb.begin(); it + 1 < vector_nb.end(); it += 2)
	{
		if (*it < *(it + 1))
			std::swap(*it, *(it + 1));
		pairs.push_back(std::make_pair(*it, *(it + 1)));
	}
	if (vector_nb.size() % 2)
		struggle = *(vector_nb.end() - 1);
	sort(pairs.begin(), pairs.end());
	for (size_t i = 0; i < pairs.size(); i++)
	{
		largest.push_back(pairs[i].first);
		lowest.push_back(pairs[i].second);
	}
	FordJhonsonVector(lowest, largest);
}

void PmergeMe::sortingInVector()
{
	double start;
	std::list<int>::iterator it;

	start = getTime();
	for (it = this->numbersConverted.begin(); it != numbersConverted.end(); it++)
		this->vector_nb.push_back(*it);
	applyFordJhonsonVec();
	this->timeOfVector = getTime() - start;
}

// ============================= Sort Deque ============================

void generateJacobsthalSequence(int size, std::deque<int>& jacobWithAllIdx)
{

	std::deque<int> jacob;
	int n;
	int min;
	int max;
	int i;

	jacob.push_back(0);
	jacob.push_back(1);
	n = 2;
	i = 0;
	while (*(jacob.end() - 1) < size)
	{
		jacob.push_back(jacob[n - 1] + 2 * jacob[n - 2]);
		n++;
	}
	jacob.erase(jacob.begin(), jacob.begin() + 2);
	i = 0;
	while (true)
	{
		max = jacob[i + 1];
		for (min = jacob[i]; max > min; max--)
			if (max <= size)
				jacobWithAllIdx.push_back(max - 1);
		if (min == jacob[jacob.size() - 2])
			break;
		i++;
	}
}

void PmergeMe::FordJhonsonDeque(std::deque<int> &lowest, std::deque<int> &largest)
{
	std::deque<int> jacobSeq;
	std::deque<int>::iterator lb;
	int val;

	if (lowest.size() >= 1)
		largest.insert(largest.begin(), *lowest.begin());
	if (lowest.size() <= 1)
		goto end;
	generateJacobsthalSequence(lowest.size(), jacobSeq);
	for (size_t i = 0; i < jacobSeq.size(); i++)
	{
		val = lowest[jacobSeq[i]];
		lb = std::lower_bound(largest.begin(), largest.end(), val);
		largest.insert(lb, val);
	}
end:
	if (this->struggle != -1)
	{
		lb = std::lower_bound(largest.begin(), largest.end(), struggle);
		largest.insert(lb, struggle);
	}
	deque_nb = largest;
}
void PmergeMe::applyFordJhonsonDeq()
{
	std::deque<std::pair<int, int> > pairs;
	std::deque<int> lowest;
	std::deque<int> largest;
	std::deque<int>::iterator it;

	for (it = deque_nb.begin(); it + 1 < deque_nb.end(); it += 2)
	{
		if (*it < *(it + 1))
			std::swap(*it, *(it + 1));
		pairs.push_back(std::make_pair(*it, *(it + 1)));
	}
	if (deque_nb.size() % 2)
		struggle = *(deque_nb.end() - 1);
	sort(pairs.begin(), pairs.end());
	for (size_t i = 0; i < pairs.size(); i++)
	{
		largest.push_back(pairs[i].first);
		lowest.push_back(pairs[i].second);
	}
	FordJhonsonDeque(lowest, largest);
}

void PmergeMe::sortingInDeque()
{
	double start;
	std::list<int>::iterator it;

	start = getTime();
	for (it = this->numbersConverted.begin(); it != numbersConverted.end(); it++)
		this->deque_nb.push_back(*it);
	applyFordJhonsonDeq();
	this->timeOfDeque = getTime() - start;
}
