#pragma once
#include <bits/stdc++.h>
#include <sys/time.h>
#include <algorithm>

typedef std::string String;

class PmergeMe
{
private:
	int struggle;
	int range;
	double timeOfVector;
	double timeOfDeque;
	std::vector<int> vector_nb;
	std::deque<int> deque_nb;
	std::list<int> numbersConverted;

	void applyFordJhonsonVec();
	void applyFordJhonsonDeq();

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void IsvalideArgs(char **argv, int ac);
	void sortingInDeque();
	void sortingInVector();
	void FordJhonsonVector(std::vector<int> &lowest, std::vector<int> &largest);
	void FordJhonsonDeque(std::deque<int> &lowest, std::deque<int> &largest);
	void print();
};
