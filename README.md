# CPP09

C++ Module 09: real-world STL application — Bitcoin price lookup with `std::map`, an RPN calculator with `std::stack`, and Ford-Johnson merge-insert sort benchmarked on `std::vector` vs `std::deque`.

## Project Overview
- What it does: three parsing-heavy exercises demonstrating practical STL container usage with real-world problem domains.
- Core themes: `std::map` ordered lookup, stack-based evaluation, merge-insert sorting, performance benchmarking.

## Architecture & Design
- **ex00 (BitcoinExchange)**: loads a CSV database into `std::map<string, double>` (date → price); for each input line, finds the closest date using `lower_bound` and computes value.
- **ex01 (RPN)**: Reverse Polish Notation calculator using `std::stack`. Tokenizes input, pushes operands, pops two for each operator.
  - Custom `Queue<T>` and `Stack<T>` wrappers over STL containers.
- **ex02 (PmergeMe)**: Ford-Johnson merge-insert sort implemented on both `std::vector<int>` and `std::deque<int>`, with `gettimeofday()`-based timing to compare container performance.
  - Pairs elements, recursively sorts the larger halves, then binary-inserts the smaller halves.

## Core Concepts (with code)
- Bitcoin date lookup with `std::map::lower_bound`:
```cpp
// BitcoinExchange.hpp
class BitcoinExchange {
    std::map<std::string, double> database;
public:
    void parseDB(std::ifstream& DB);      // load CSV into map
    void exchange(std::ifstream& input);   // lookup + compute
};
// Usage: lower_bound finds closest date <= query date
```
- Ford-Johnson on two containers:
```cpp
// PmergeMe.hpp
class PmergeMe {
    std::vector<int> vector_nb;
    std::deque<int> deque_nb;
    double timeOfVector, timeOfDeque;
public:
    void FordJhonsonVector(std::vector<int>& lowest, std::vector<int>& largest);
    void FordJhonsonDeque(std::deque<int>& lowest, std::deque<int>& largest);
    void print();  // before/after + timing comparison
};
```

## Code Walkthrough
1) ex00: parse CSV database (date,value); for each input line, validate date format and value range [0, 1000]; find closest date in map; print `date => value * rate`.
2) ex01: tokenize RPN expression by spaces; digits push to stack; operators pop two, compute, push result. Final stack top = answer.
3) ex02: validate args (positive integers); pair elements, sort larger halves recursively, binary-insert smaller halves. Run on both vector and deque; print before/after arrays and timing.

## Installation & Setup
- `make` per exercise (C++98).
- ex00: `./btc input.txt` (requires `data.csv` database file).
- ex01: `./RPN "3 4 + 2 *"` → `14`.
- ex02: `./PmergeMe 3 5 9 7 4` → sorted output + timing.

## Usage Guide
```bash
./btc input.txt           # Bitcoin value lookup
./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"  # = 42
./PmergeMe 3 5 9 7 4      # merge-insert sort with timing
```

## Technical Deep Dive
- `std::map::lower_bound` gives O(log n) date lookup; if exact date missing, uses the closest earlier date.
- RPN: O(n) time and space; validates single-digit operands per subject constraint.
- Ford-Johnson (merge-insert) aims for fewer comparisons than standard merge sort; uses binary insertion for the "struggle" elements.
- `gettimeofday()` provides microsecond timing; vector vs deque comparison shows cache-locality effects.

## Improvements & Future Work
- Support multi-digit operands in RPN.
- Add Jacobsthal number sequence for optimal binary insertion order in Ford-Johnson.
- Visualize the merge-insert tree for educational purposes.

## Author
Oualid Obbad (@oualidobbad)