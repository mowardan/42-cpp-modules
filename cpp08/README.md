# CPP08 — STL Containers, Iterators, and Algorithms

## Overview

CPP08 introduces the **Standard Template Library (STL)** — the collection of containers, iterators, and algorithms that form the backbone of practical C++ programming. The module covers searching containers with algorithms, implementing a custom container-like class, and extending existing STL containers through inheritance.

## Learning Objectives

- STL containers (`std::vector`, `std::stack`)
- STL algorithms (`std::find`, `std::sort`, `std::min_element`, `std::max_element`, `std::adjacent_find`)
- Iterators (begin/end, iterator typedefs)
- Function templates with container type parameters
- Extending STL containers through inheritance
- Container adaptor internals (`std::stack` and the protected `c` member)

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Easy find | `std::find`, templates, iterators | Search for an integer in any STL container |
| ex01 | Span | `std::vector`, `std::sort`, min/max algorithms | Store numbers and compute shortest/longest span |
| ex02 | MutantStack | Inheriting from STL, exposing iterators | `std::stack` with iterator support |

---

## ex00 — easyfind

**Files:** `easyfind.hpp`, `main.cpp`

A function template that searches for an integer value in any container:

```cpp
template <typename T>
typename T::iterator easyfind(T& container, int value) {
    typename T::iterator it = std::find(container.begin(), container.end(), value);
    if (it == container.end())
        throw std::runtime_error("Value not found in container");
    return it;
}
```

### Key Points

- **`typename T::iterator`**: The `typename` keyword is required because `T::iterator` is a dependent type — the compiler doesn't know it's a type until `T` is resolved
- **`std::find`**: A linear-search algorithm from `<algorithm>` that returns an iterator to the first match, or `end()` if not found
- **Generic**: Works with any container that provides `begin()`, `end()`, and an iterator type (`std::vector`, `std::list`, `std::deque`, etc.)

```cpp
std::vector<int> vec;
vec.push_back(1); vec.push_back(2); vec.push_back(3);

std::vector<int>::iterator it = easyfind(vec, 3);  // Found
easyfind(vec, 6);  // Throws std::runtime_error
```

---

## ex01 — Span

**Files:** `Span.hpp`, `Span.cpp`, `main.cpp`

A class that stores up to N integers and computes the shortest and longest span (difference) between them.

### Class Design

```cpp
class Span {
    unsigned int N;            // Maximum capacity
    std::vector<int> numbers;  // Internal storage

public:
    Span(unsigned int n);
    void addNumber(int number);     // Throws if full
    int shortestSpan() const;       // Minimum difference between any two numbers
    int longestSpan() const;        // Maximum difference (max - min)
};
```

### Algorithm Implementation

**Shortest Span**: Sort a copy of the numbers, then find the minimum difference between adjacent elements:

```cpp
int Span::shortestSpan() const {
    std::vector<int> sorted = numbers;
    std::sort(sorted.begin(), sorted.end());

    int minSpan = std::numeric_limits<int>::max();
    for (size_t i = 1; i < sorted.size(); ++i) {
        int span = sorted[i] - sorted[i - 1];
        if (span < minSpan)
            minSpan = span;
    }
    return minSpan;
}
```

**Longest Span**: Simply the difference between the maximum and minimum elements:

```cpp
int Span::longestSpan() const {
    int minNumber = *std::min_element(numbers.begin(), numbers.end());
    int maxNumber = *std::max_element(numbers.begin(), numbers.end());
    return maxNumber - minNumber;
}
```

Both methods throw if fewer than 2 numbers are stored.

### STL Algorithms Used

| Algorithm | Header | Purpose |
|-----------|--------|---------|
| `std::sort` | `<algorithm>` | Sort elements in ascending order |
| `std::min_element` | `<algorithm>` | Find iterator to smallest element |
| `std::max_element` | `<algorithm>` | Find iterator to largest element |

---

## ex02 — MutantStack

**Files:** `MutantStack.hpp`, `main.cpp`

A `std::stack` with iterator support, implemented by inheriting from `std::stack` and exposing its protected underlying container.

### Implementation

```cpp
template <typename T>
class MutantStack : public std::stack<T> {
public:
    typedef typename std::stack<T>::container_type::iterator iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;

    iterator begin()       { return std::stack<T>::c.begin(); }
    iterator end()         { return std::stack<T>::c.end(); }
    const_iterator begin() const { return std::stack<T>::c.begin(); }
    const_iterator end()   const { return std::stack<T>::c.end(); }
};
```

### Why `std::stack` Lacks Iterators

`std::stack` is a **container adaptor** — a wrapper around an underlying container (default: `std::deque`). By design, it exposes only `push()`, `pop()`, `top()`, `size()`, and `empty()` to enforce LIFO (Last-In, First-Out) semantics. Iterators would break this abstraction.

### How `MutantStack` Works

`std::stack` stores its underlying container as a **protected** member called `c`. Because `MutantStack` inherits from `std::stack`, it can access `c` directly and expose its iterators:

```
std::stack<T>
├── protected: container_type c;    ← std::deque<T> by default
│   ├── begin() → iterator
│   └── end()   → iterator
├── push(), pop(), top()            ← public LIFO interface

MutantStack<T> : public std::stack<T>
├── begin() → c.begin()            ← Exposes underlying iterators
└── end()   → c.end()
```

### Usage

```cpp
MutantStack<int> mstack;
mstack.push(5);
mstack.push(17);
mstack.push(3);

MutantStack<int>::iterator it = mstack.begin();
while (it != mstack.end()) {
    std::cout << *it << std::endl;  // 5, 17, 3 (insertion order)
    ++it;
}

std::stack<int> s(mstack);  // MutantStack is compatible with std::stack
```

---

## Technical Concepts

### STL Architecture

The STL is built on three pillars:

```
Containers          Algorithms          Iterators
(store data)        (operate on data)   (connect containers to algorithms)
  vector              find                input_iterator
  deque               sort                output_iterator
  list                min_element         forward_iterator
  map                 max_element         bidirectional_iterator
  stack               adjacent_find       random_access_iterator
```

Algorithms operate on **iterator ranges** `[begin, end)`, not on containers directly. This decoupling allows any algorithm to work with any container.

### Iterator Categories

| Category | Operations | Containers |
|----------|-----------|------------|
| Input | Read, `++` | `istream_iterator` |
| Forward | Read/write, `++` | `forward_list` |
| Bidirectional | Read/write, `++`, `--` | `list`, `map`, `set` |
| Random Access | Read/write, `++`, `--`, `+n`, `[i]` | `vector`, `deque` |

`std::sort` requires random-access iterators, which is why it works with `vector` and `deque` but not `list`.

### Container Adaptors

`std::stack`, `std::queue`, and `std::priority_queue` are not true containers — they are **adaptors** that wrap an underlying container and restrict its interface:

| Adaptor | Default Container | Interface |
|---------|------------------|-----------|
| `std::stack` | `std::deque` | LIFO: push, pop, top |
| `std::queue` | `std::deque` | FIFO: push, pop, front, back |
| `std::priority_queue` | `std::vector` | Heap: push, pop, top |

## Compilation

```bash
cd ex00 && make && ./easyfind
cd ex01 && make && ./Span
cd ex02 && make && ./MutantStack
```

## Key Takeaways

- STL algorithms operate on iterator ranges, not containers — this enables maximum reusability
- `typename` is required before dependent types in templates (`typename T::iterator`)
- STL container adaptors intentionally restrict interfaces to enforce access patterns
- Inheriting from STL containers provides access to protected members like the underlying container
- `std::sort` + adjacent difference is an efficient O(n log n) approach to finding the minimum span
