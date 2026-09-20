# CPP09 — STL Practical Applications

## Overview

CPP09 is the final module, applying STL containers and algorithms to real-world problems: financial data processing, mathematical expression evaluation, and sorting algorithm implementation. Each exercise mandates the use of specific containers and requires handling production-quality concerns like input validation, error handling, and performance measurement.

## Learning Objectives

- `std::map` for key-value storage and ordered lookup
- `std::stack` for expression evaluation
- `std::vector` and `std::deque` for sorting algorithms
- File parsing and CSV/TSV data processing
- Input validation and error reporting
- Algorithm complexity and performance benchmarking
- Ford-Johnson merge-insert sort with Jacobsthal sequence optimization

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Bitcoin Exchange | `std::map`, file I/O, date validation | Look up historical Bitcoin exchange rates |
| ex01 | Reverse Polish Notation | `std::stack`, expression parsing | Evaluate RPN mathematical expressions |
| ex02 | PmergeMe | `std::vector`, `std::deque`, sorting | Ford-Johnson merge-insert sort with benchmarking |

---

## ex00 — Bitcoin Exchange

**Files:** `BitcoinExchange.hpp`, `BitcoinExchange.cpp`, `main.cpp`

### Problem

Given a CSV database of historical Bitcoin prices and an input file of dates with values, compute the portfolio value for each entry using the exchange rate on that date (or the nearest earlier date).

### Class Design

```cpp
class BitcoinExchange {
    std::map<std::string, double> db;  // date → exchange rate

public:
    void loadDatabase();                          // Parse data.csv
    void processInput(const std::string& filename); // Process user input file
    double getRate(const std::string& date);      // Find rate (or nearest earlier)
    bool isValidDate(const std::string& date);    // YYYY-MM-DD validation
    bool isValidValue(const std::string& value);  // Numeric validation
    std::string trim(const std::string& str);     // Whitespace trimming
};
```

### Why `std::map`?

`std::map` is an ordered associative container (typically implemented as a red-black tree). It provides:
- **O(log n)** lookup by key
- **Ordered iteration** — dates are stored in chronological order
- **`lower_bound()`** — finds the nearest key ≥ the target, enabling "closest earlier date" lookup

### Rate Lookup Algorithm

```cpp
double BitcoinExchange::getRate(const std::string& date) {
    std::map<std::string, double>::iterator it = db.find(date);
    if (it != db.end())
        return it->second;             // Exact match

    std::map<std::string, double>::iterator lower = db.lower_bound(date);
    if (lower == db.begin())
        return lower->second;          // No earlier date exists
    --lower;                           // Step back to nearest earlier date
    return lower->second;
}
```

### Input Validation

The implementation validates:
- Date format (YYYY-MM-DD with correct separators)
- Date semantics (valid month 1–12, correct days per month, leap year handling)
- Value is a valid number, non-negative, and ≤ 1000
- Input file format (date | value delimiter)

---

## ex01 — RPN Calculator

**Files:** `RPN.hpp`, `RPN.cpp`, `main.cpp`

### Problem

Evaluate a mathematical expression in Reverse Polish Notation (postfix notation) using a stack.

### How RPN Works

In RPN, operators follow their operands:

```
Infix:    (3 + 4) * 2
RPN:      3 4 + 2 *

Evaluation with stack:
  Token  Stack
  3      [3]
  4      [3, 4]
  +      [7]        ← pop 3 and 4, push 3+4
  2      [7, 2]
  *      [14]       ← pop 7 and 2, push 7*2
  Result: 14
```

### Implementation

```cpp
void RPN::evaluate(const std::string& str) {
    std::istringstream iss(str);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) { std::cerr << "Error" << std::endl; return; }
            int b = stack.top(); stack.pop();
            int a = stack.top(); stack.pop();

            if (token == "+") stack.push(a + b);
            else if (token == "-") stack.push(a - b);
            else if (token == "*") stack.push(a * b);
            else {
                if (b == 0) { std::cerr << "Error" << std::endl; return; }
                stack.push(a / b);
            }
        }
        else if (token.length() == 1 && std::isdigit(token[0])) {
            stack.push(token[0] - '0');  // Single digit only
        }
        else {
            std::cerr << "Error" << std::endl; return;
        }
    }

    if (stack.size() != 1) { std::cerr << "Error" << std::endl; return; }
    std::cout << stack.top() << std::endl;
}
```

### Error Handling

- Division by zero
- Insufficient operands for an operator
- Invalid tokens (non-digit, multi-digit numbers)
- Malformed expressions (stack doesn't reduce to exactly one value)

### Why `std::stack`?

RPN evaluation naturally follows LIFO semantics. Operands are pushed, and operators pop the top two values. `std::stack` enforces this access pattern and prevents accidental random access into the evaluation state.

---

## ex02 — PmergeMe (Ford-Johnson Merge-Insert Sort)

**Files:** `PmergeMe.hpp`, `PmergeMe.cpp`, `main.cpp`

### Problem

Sort a sequence of positive integers using the Ford-Johnson merge-insert sort algorithm, implemented with both `std::vector` and `std::deque`, and compare their performance.

### Algorithm Overview

The Ford-Johnson algorithm minimizes the number of comparisons needed to sort:

1. **Pair elements**: Group the input into pairs, identify the winner (larger) and loser (smaller) in each pair
2. **Recursively sort winners**: Sort only the winner chain recursively
3. **Build main chain**: The sorted winners form the main sorted sequence
4. **Insert losers**: Insert losers into the main chain using binary search, with insertion order determined by the **Jacobsthal sequence** to minimize comparisons

### Jacobsthal Sequence

The Jacobsthal sequence determines the optimal order for inserting pending elements:

```
J(0) = 0, J(1) = 1, J(n) = J(n-1) + 2 * J(n-2)
Sequence: 0, 1, 1, 3, 5, 11, 21, 43, ...
```

Elements are inserted in reverse order within each Jacobsthal group, reducing the number of binary search comparisons by keeping the search range small.

### Dual Container Implementation

The algorithm is implemented identically for both `std::vector` and `std::deque`:

```cpp
void PmergeMe::sortVector(std::vector<int>& sequence);
void PmergeMe::sortDeque(std::deque<int>& sequence);
```

### Performance Benchmarking

```cpp
clock_t startVec = clock();
A.sortVector(S1);
clock_t endVec = clock();
double timeVec = double(endVec - startVec) / CLOCKS_PER_SEC * 1000000;

std::cout << "Time to process a range of " << S1.size()
          << " elements with std::vector : " << timeVec << " us" << std::endl;
```

### Input Validation

- Only positive integers accepted
- No duplicate numbers allowed (checked via sort + `std::adjacent_find`)
- Numbers must fit in `int` range
- At least one number required

### Usage

```bash
./PmergeMe 3 5 9 7 4
# Output:
# Before: 3 5 9 7 4
# After:  3 4 5 7 9
# Time to process a range of 5 elements with std::vector : X.XXXXX us
# Time to process a range of 5 elements with std::deque  : X.XXXXX us
```

---

## Technical Concepts

### Container Choice Justification

| Exercise | Container | Why |
|----------|-----------|-----|
| ex00 | `std::map` | Ordered key-value pairs with O(log n) lookup and `lower_bound` |
| ex01 | `std::stack` | LIFO semantics match RPN evaluation perfectly |
| ex02 | `std::vector` | Contiguous memory, cache-friendly, O(1) random access |
| ex02 | `std::deque` | Efficient front/back insertion, random access, segmented memory |

### `std::vector` vs `std::deque` Performance

| Operation | `std::vector` | `std::deque` |
|-----------|--------------|--------------|
| Random access | O(1) — contiguous | O(1) — indexed segments |
| Push back | Amortized O(1) | O(1) |
| Push front | O(n) — shifts all | O(1) |
| Insert middle | O(n) | O(n) |
| Cache locality | Excellent | Good (segmented) |
| Memory layout | Single block | Block array |

For sorting, `std::vector` typically outperforms `std::deque` due to superior cache locality from contiguous memory allocation.

### `std::map::lower_bound`

`lower_bound(key)` returns an iterator to the first element whose key is **not less than** `key`. This enables efficient "find the closest earlier date" queries:

```cpp
auto it = db.lower_bound("2023-06-15");
// If exact match: it points to the entry
// If no exact match: it points to the NEXT date
// Decrement (--it) to get the nearest earlier date
```

### Ford-Johnson Complexity

The Ford-Johnson algorithm achieves close to the **information-theoretic lower bound** on comparisons:

- For n elements, the minimum comparisons needed is ⌈log₂(n!)⌉
- Ford-Johnson uses approximately n⌈log₂n⌉ - 2^⌈log₂n⌉ + 1 comparisons
- This is optimal or near-optimal for small to medium n

## Compilation

```bash
cd ex00 && make && ./btc input.txt
cd ex01 && make && ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
cd ex02 && make && ./PmergeMe 3 5 9 7 4
```

## Key Takeaways

- Choose containers based on access patterns: `map` for key-value lookup, `stack` for LIFO, `vector` for sorting
- `std::map::lower_bound` enables efficient nearest-key queries in O(log n)
- RPN evaluation is a textbook stack application — each operator pops two values and pushes one
- Ford-Johnson merge-insert sort minimizes comparisons using the Jacobsthal sequence for optimal insertion ordering
- Benchmarking with `clock()` provides microsecond-level timing to compare container performance
- Input validation is critical in production code — validate types, ranges, duplicates, and format
