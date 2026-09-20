# 42 C++ Modules

[![42 C++ Modules CI](https://github.com/mowardan/42-cpp-modules/actions/workflows/ci.yml/badge.svg)](https://github.com/mowardan/42-cpp-modules/actions/workflows/ci.yml)
![C++ Standard](https://img.shields.io/badge/C%2B%2B-98-blue.svg)
![Compilers](https://img.shields.io/badge/Compilers-GCC%20%7C%20Clang-green.svg)
![42 Network](https://img.shields.io/badge/42-1337-black.svg)

A comprehensive collection of C++ projects completed as part of the 42 School curriculum, covering fundamental through advanced C++ concepts across ten progressive modules.

## About

The C++ modules at 42 School form a structured introduction to object-oriented programming and modern C++ practices. Starting from basic syntax and I/O operations, the curriculum advances through class design, inheritance hierarchies, polymorphism, exception handling, templates, and STL containers — building a solid foundation in C++ software engineering.

All modules are written in **C++98** and compiled with `c++ -Wall -Wextra -Werror -std=c++98`.

## Curriculum Overview

| Module | Topics | Exercises | Documentation |
|--------|--------|-----------|---------------|
| **CPP00** | Classes, member functions, I/O streams, static | 2 | [README](cpp00/README.md) |
| **CPP01** | Memory allocation, references, pointers, file streams | 6 | [README](cpp01/README.md) |
| **CPP02** | Orthodox Canonical Form, operator overloading, fixed-point | 3 | [README](cpp02/README.md) |
| **CPP03** | Inheritance, construction/destruction chaining | 3 | [README](cpp03/README.md) |
| **CPP04** | Polymorphism, abstract classes, deep copy | 3 | [README](cpp04/README.md) |
| **CPP05** | Exceptions, nested exception classes, abstract forms | 4 | [README](cpp05/README.md) |
| **CPP06** | C++ type casting (static, reinterpret, dynamic) | 3 | [README](cpp06/README.md) |
| **CPP07** | Function and class templates | 3 | [README](cpp07/README.md) |
| **CPP08** | STL containers, iterators, algorithms | 3 | [README](cpp08/README.md) |
| **CPP09** | STL practical applications, sorting algorithms | 3 | [README](cpp09/README.md) |

## Repository Structure

```
42-cpp-modules/
├── cpp00/          # C++ fundamentals
│   ├── ex00/       # Megaphone (string manipulation)
│   └── ex01/       # PhoneBook (classes, I/O formatting)
├── cpp01/          # Memory & references
│   ├── ex00/       # Zombie (stack vs heap)
│   ├── ex01/       # Zombie horde (heap arrays)
│   ├── ex02/       # Pointers vs references
│   ├── ex03/       # Weapon (references vs pointers in classes)
│   ├── ex04/       # File stream replace
│   └── ex05/       # Harl (pointers to member functions)
├── cpp02/          # Operator overloading
│   ├── ex00/       # Fixed-point (canonical form)
│   ├── ex01/       # Fixed-point (constructors, conversions)
│   └── ex02/       # Fixed-point (full operator overloading)
├── cpp03/          # Inheritance
│   ├── ex00/       # ClapTrap
│   ├── ex01/       # ClapTrap + ScavTrap
│   └── ex02/       # ClapTrap + ScavTrap + FragTrap
├── cpp04/          # Polymorphism
│   ├── ex00/       # Virtual functions (Animal hierarchy)
│   ├── ex01/       # Deep copy with Brain
│   └── ex02/       # Abstract classes (pure virtual)
├── cpp05/          # Exceptions
│   ├── ex00/       # Bureaucrat (grade exceptions)
│   ├── ex01/       # Form (sign validation)
│   ├── ex02/       # Concrete forms (execute actions)
│   └── ex03/       # Intern (form factory)
├── cpp06/          # C++ casts
│   ├── ex00/       # ScalarConverter (static_cast)
│   ├── ex01/       # Serializer (reinterpret_cast)
│   └── ex02/       # Type identification (dynamic_cast)
├── cpp07/          # Templates
│   ├── ex00/       # Function templates (swap, min, max)
│   ├── ex01/       # iter (function template with callback)
│   └── ex02/       # Array (class template)
├── cpp08/          # STL
│   ├── ex00/       # easyfind (algorithm + containers)
│   ├── ex01/       # Span (vector operations)
│   └── ex02/       # MutantStack (stack with iterators)
└── cpp09/          # STL applications
    ├── ex00/       # BitcoinExchange (map, file parsing)
    ├── ex01/       # RPN calculator (stack)
    └── ex02/       # PmergeMe (merge-insert sort, benchmarking)
```

## Skills Demonstrated

**Core C++**
- Object-oriented design with classes, encapsulation, and access control
- Memory management (stack vs heap allocation, `new`/`delete`)
- References and pointers (ownership semantics, const-correctness)
- Orthodox Canonical Form (constructor, copy constructor, assignment, destructor)

**Object-Oriented Programming**
- Single inheritance and construction/destruction ordering
- Runtime polymorphism with virtual functions and vtables
- Abstract classes with pure virtual methods
- Operator overloading (arithmetic, comparison, insertion, increment/decrement)

**Advanced Features**
- Exception handling with custom nested exception classes
- C++ type casting (`static_cast`, `reinterpret_cast`, `dynamic_cast`)
- Function and class templates with generic programming
- STL containers (`vector`, `deque`, `stack`, `map`), iterators, and algorithms

**Design Patterns**
- Factory pattern (Intern creating forms)
- Template Method pattern (AForm base with executeAction hook)
- Adapter pattern (MutantStack exposing iterators on std::stack)

## Compilation and Usage

Each exercise contains its own `Makefile`. To build and run any exercise:

```bash
# Navigate to the exercise directory
cd cpp05/ex02

# Build
make

# Run (binary name varies per exercise — check the Makefile)
./AForm

# Clean build artifacts
make clean    # Remove object files
make fclean   # Remove object files and binary
make re       # Full rebuild
```

### Prerequisites

- A C++ compiler supporting C++98 (`c++`, `g++`, or `clang++`)
- `make`

## Learning Approach

Each module in this curriculum builds upon the previous one. The progression is intentional:

1. **Understand the problem** a feature solves before using it
2. **Know the trade-offs** — virtual functions add vtable overhead; templates increase binary size
3. **Respect constraints** — writing C++98 forces understanding of what later standards automated
4. **Design before coding** — class hierarchies and ownership models should be planned, not discovered

The code in this repository reflects working through these concepts progressively, with each module introducing a focused set of new features while reinforcing patterns from earlier modules.

## CI/CD Pipeline

The repository includes a comprehensive GitHub Actions workflow (`.github/workflows/ci.yml`) that runs on every push and pull request:

- 🔨 **Multi-Compiler Builds**: Compiles all 31 exercises across GCC (`g++`) and Clang (`clang++`) with `-Wall -Wextra -Werror -std=c++98`.
- 🧪 **Automated Runtime Tests**: Validates output and execution across non-interactive exercises.
- 🛡️ **AddressSanitizer (ASan)**: Detects memory leaks, buffer overflows, and undefined memory behavior.
- 🔍 **Static Analysis**: Runs `cppcheck` with C++03 profile to identify potential style, performance, and portability issues.
- 🔄 **Rebuild Verification**: Ensures `make re` performs clean rebuilds across all Makefiles.
- 📐 **42 Standards Compliance**: Verifies 42 headers, include guards, and standard Makefile targets (`all`, `clean`, `fclean`, `re`).

## Author

- GitHub: [mowardan](https://github.com/mowardan)
- 42 Intra: mowardan
- School: 1337 (42 Network)
