#pragma once
#include <bits/stdc++.h>
#include <sys/time.h>

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

	void pairSortElementVector();
	void pairSortElementDeque();

public:
	PmergeMe();
	PmergeMe(const PmergeMe &other);
	PmergeMe &operator=(const PmergeMe &other);
	~PmergeMe();
	void IsvalideArgs(char **argv, int ac);
	void sortingInDeque();
	void sortingInVector();
	void print();
};
