# CPP01 — Memory, References, and Pointers

## Overview

CPP01 explores the fundamental distinction between stack and heap memory in C++, introduces references as an alternative to pointers, and covers file stream operations. The module builds on CPP00's class foundations by adding dynamic memory allocation, pointer-to-member functions, and practical string processing.

## Learning Objectives

- Stack vs heap allocation (`new` / `delete`, `new[]` / `delete[]`)
- Pointers vs references (syntax, semantics, ownership implications)
- When to use references vs pointers in class design
- File I/O with `std::ifstream` and `std::ofstream`
- Pointers to member functions
- String search and replacement without `std::string::replace`

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | BraiiiiiiinnnzzzZ | `new`/`delete`, stack vs heap | Create Zombie objects on stack and heap |
| ex01 | Moar brainz! | `new[]`/`delete[]`, heap arrays | Allocate and manage a horde of Zombies |
| ex02 | HI THIS IS BRAIN | Pointers vs references | Compare addresses and values of pointer and reference to same variable |
| ex03 | Unnecessary violence | Reference vs pointer members | Two classes using a Weapon — one by reference, one by pointer |
| ex04 | Sed is for losers | File streams, string operations | Replace all occurrences of a string in a file |
| ex05 | Harl 2.0 | Pointers to member functions | Dispatch log levels using function pointer array |

---

## ex00 — BraiiiiiiinnnzzzZ

**Files:** `Zombie.hpp`, `Zombie.cpp`, `newZombie.cpp`, `randomChump.cpp`, `main.cpp`

Demonstrates the difference between stack and heap allocation through two factory patterns:

- **`newZombie(name)`**: Allocates a Zombie on the heap with `new` and returns the pointer — the caller is responsible for `delete`
- **`randomChump(name)`**: Creates a Zombie on the stack — it is automatically destroyed when the function returns

```cpp
Zombie* newZombie(std::string name) {
    Zombie* z = new Zombie(name);  // heap — survives function scope
    return z;
}

void randomChump(std::string name) {
    Zombie z(name);   // stack — destroyed at closing brace
    z.announce();
}
```

---

## ex01 — Moar brainz!

**Files:** `Zombie.hpp`, `Zombie.cpp`, `zombieHorde.cpp`, `main.cpp`

Extends the Zombie concept to array allocation. `zombieHorde(N, name)` allocates an array of N Zombies on the heap using `new[]`, sets each name via `setName()`, and returns the array pointer.

The caller deallocates the entire array with a single `delete[]` call. This exercise requires a default constructor (unlike ex00) because `new Zombie[N]` must default-construct each element before `setName()` is called.

---

## ex02 — HI THIS IS BRAIN

**Files:** `main.cpp`

A short demonstration that a pointer and a reference to the same variable share the same memory address and value:

```cpp
std::string str = "HI THIS IS BRAIN";
std::string* stringPTR = &str;    // pointer: stores address
std::string& stringREF = str;     // reference: alias for str
```

All three (`&str`, `stringPTR`, `&stringREF`) print the same address. All three (`str`, `*stringPTR`, `stringREF`) print the same value.

---

## ex03 — Unnecessary violence

**Files:** `Weapon.hpp`, `Weapon.cpp`, `HumanA.hpp`, `HumanA.cpp`, `HumanB.hpp`, `HumanB.cpp`, `main.cpp`

Two Human classes interact with a `Weapon` to demonstrate when to use references vs pointers:

| Class | Weapon storage | Rationale |
|-------|---------------|-----------|
| `HumanA` | `Weapon& weapon` (reference) | Always has a weapon — set at construction, cannot be null |
| `HumanB` | `Weapon* weapon` (pointer) | May not have a weapon — initialized to `NULL`, set later via `setWeapon()` |

The `Weapon` class provides `getType()` returning a const reference and `setType()` accepting a const reference, demonstrating how references avoid unnecessary copies.

When `club.setType("some other type of club")` is called, both `HumanA` and `HumanB` see the updated weapon type because they hold a reference/pointer to the same `Weapon` object — not a copy.

---

## ex04 — Sed is for losers

**Files:** `replace.hpp`, `main.cpp`

A file processing program that reads a file, replaces all occurrences of string `s1` with string `s2`, and writes the result to a new file named `<filename>.replace`.

### Implementation

1. Opens input file with `std::ifstream`
2. Reads entire file content into a `std::string` using `std::getline` in a loop
3. Performs replacement using `std::string::find()`, `erase()`, and `insert()` — avoids using `std::string::replace()` as required by the subject
4. Writes result to output file with `std::ofstream`

```bash
./replace input.txt "Hello" "Goodbye"
# Creates input.txt.replace with all "Hello" replaced by "Goodbye"
```

---

## ex05 — Harl 2.0

**Files:** `Harl.hpp`, `Harl.cpp`, `main.cpp`

Implements a complaint system using **pointers to member functions** to dispatch log levels without `if/else` chains.

### Design

```cpp
void Harl::complain(std::string level) {
    void (Harl::*functions[])(void) = {
        &Harl::debug, &Harl::info, &Harl::warning, &Harl::error
    };
    std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    for (size_t i = 0; i < 4; i++) {
        if (level == levels[i]) {
            (this->*functions[i])();  // call via member function pointer
            return;
        }
    }
}
```

Each log level (`DEBUG`, `INFO`, `WARNING`, `ERROR`) maps to a private member function. The `complain()` method uses an array of member function pointers paired with a string array to find and invoke the correct handler.

### Why Pointers to Member Functions?

- Eliminates repetitive `if/else` or `switch` blocks
- Adding a new log level requires only adding one entry to each array
- Demonstrates that functions in C++ are first-class addressable entities, even when bound to a class instance

---

## Technical Concepts

### Stack vs Heap Allocation

| Aspect | Stack | Heap |
|--------|-------|------|
| **Lifetime** | Automatic — destroyed at scope exit | Manual — persists until `delete` |
| **Speed** | Fast (pointer bump) | Slower (allocator overhead) |
| **Size** | Limited (typically 1-8 MB) | Large (limited by system memory) |
| **Syntax** | `Zombie z("name");` | `Zombie* z = new Zombie("name");` |
| **Cleanup** | Automatic | Programmer's responsibility |

### References vs Pointers

| Feature | Reference | Pointer |
|---------|-----------|---------|
| **Can be null** | No | Yes |
| **Can be reassigned** | No | Yes |
| **Syntax** | `T& ref = obj;` | `T* ptr = &obj;` |
| **Access** | Direct: `ref.method()` | Dereference: `ptr->method()` |
| **Use when** | Object always exists | Object may not exist, or may change |

## Compilation

Each exercise has its own Makefile:

```bash
cd ex00 && make && ./Zombie
cd ex01 && make && ./ZombieHorde
cd ex02 && make && ./brain
cd ex03 && make && ./violence
cd ex04 && make && ./replace <file> <s1> <s2>
cd ex05 && make && ./Harl
```

## Key Takeaways

- Heap allocation is necessary when objects must outlive their creating scope
- Always pair `new` with `delete` and `new[]` with `delete[]` — mixing them is undefined behavior
- References provide safer, cleaner syntax when nullability is not needed
- File I/O in C++ uses the same stream interface as `std::cout`/`std::cin`
- Pointers to member functions enable table-driven dispatch patterns
