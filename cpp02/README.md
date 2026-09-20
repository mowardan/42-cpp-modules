# CPP02 — Orthodox Canonical Form and Operator Overloading

## Overview

CPP02 introduces two foundational C++ practices: the **Orthodox Canonical Form** (a class design pattern ensuring correct copy semantics) and **operator overloading** (allowing user-defined types to work with built-in operators). These concepts are explored through the implementation of a fixed-point number class, which represents fractional values using integer arithmetic.

## Learning Objectives

- Orthodox Canonical Form (default constructor, copy constructor, copy assignment operator, destructor)
- Operator overloading (arithmetic, comparison, increment/decrement, stream insertion)
- Fixed-point number representation
- Conversion between integer, floating-point, and fixed-point formats
- Static member functions (`min`, `max`)
- `const` overloads for member functions

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | My First Class in Orthodox Canonical Form | Canonical form, copy semantics | Basic `Fixed` class with raw bits getter/setter |
| ex01 | Towards a more useful fixed-point number class | Type conversion constructors, `operator<<` | Add int/float constructors and `toInt()`/`toFloat()` conversions |
| ex02 | Now we're talking | Full operator overloading | Complete set of arithmetic, comparison, and increment/decrement operators |

---

## ex00 — Orthodox Canonical Form

**Files:** `Fixed.hpp`, `Fixed.cpp`, `main.cpp`

Implements a minimal `Fixed` class following the Orthodox Canonical Form. The class stores a fixed-point value as an `int` with 8 fractional bits (stored as a `static const int`).

### The Four Required Members

```cpp
Fixed();                                    // Default constructor
Fixed(const Fixed& other);                  // Copy constructor
Fixed& operator=(const Fixed& other);       // Copy assignment operator
~Fixed();                                   // Destructor
```

Each constructor and destructor prints a message to demonstrate the order of operations. The copy assignment operator includes a self-assignment check (`if (this != &other)`) to prevent issues when an object is assigned to itself.

---

## ex01 — Towards a More Useful Fixed-Point Class

**Files:** `Fixer.hpp`, `Fixer.cpp`, `main.cpp`

Extends the `Fixed` class with type-converting constructors and a stream insertion operator.

### Added Constructors

```cpp
Fixed(const int intValue);      // Converts int to fixed-point: value << 8
Fixed(const float floatValue);  // Converts float to fixed-point: roundf(value * 256)
```

### Conversion Methods

```cpp
int toInt() const;    // fixed-point → int:   value >> 8
float toFloat() const; // fixed-point → float: value / 256.0
```

### Stream Insertion Operator

```cpp
std::ostream& operator<<(std::ostream& os, const Fixed& obj) {
    os << obj.toFloat();  // Outputs the floating-point representation
    return os;
}
```

This is a **non-member** overload because the left operand is `std::ostream`, not `Fixed`.

### How Fixed-Point Works

Fixed-point arithmetic stores fractional numbers as integers by reserving a set number of bits for the fractional part:

```
Integer: 42       → Fixed-point: 42 << 8 = 10752
Float:   42.42f   → Fixed-point: roundf(42.42 * 256) = 10860
Fixed 10860       → Float: 10860 / 256.0 = 42.421875
Fixed 10860       → Int: 10860 >> 8 = 42
```

With 8 fractional bits, the precision is 1/256 ≈ 0.00390625.

---

## ex02 — Full Operator Overloading

**Files:** `Fixer.hpp`, `Fixer.cpp`, `main.cpp`

Completes the `Fixed` class with a comprehensive set of overloaded operators.

### Comparison Operators (6)

`>`, `<`, `>=`, `<=`, `==`, `!=` — all compare the underlying integer values directly.

### Arithmetic Operators (4)

`+`, `-`, `*`, `/` — convert to float, perform the operation, and construct a new `Fixed` from the result.

### Increment/Decrement Operators (4)

```cpp
Fixed& operator++();      // Pre-increment:  ++value, return *this
Fixed  operator++(int);   // Post-increment: save copy, ++value, return copy
Fixed& operator--();      // Pre-decrement
Fixed  operator--(int);   // Post-decrement
```

The pre-increment modifies and returns the object directly. The post-increment creates a copy, modifies the original, and returns the copy — this is why post-increment is slightly less efficient.

The increment/decrement operates on the raw fixed-point value, meaning `++a` adds the smallest representable epsilon (1/256).

### Static Min/Max Functions

```cpp
static Fixed& min(Fixed& a, Fixed& b);
static const Fixed& min(const Fixed& a, const Fixed& b);
static Fixed& max(Fixed& a, Fixed& b);
static const Fixed& max(const Fixed& a, const Fixed& b);
```

Two overloads per function: one for mutable references and one for const references. This allows `min`/`max` to work with both const and non-const `Fixed` objects.

---

## Technical Concepts

### Orthodox Canonical Form

A C++ class that manages resources (or may be copied) should implement these four members:

| Member | Purpose | Default Behavior |
|--------|---------|-----------------|
| Default constructor | Initialize to a valid state | Zero-initialization for POD types |
| Copy constructor | Create a new object as a copy | Memberwise copy (shallow) |
| Copy assignment | Assign from another object | Memberwise assignment (shallow) |
| Destructor | Release resources | Nothing for POD types |

**Why it matters:** If a class owns heap memory and only uses the compiler-generated copy constructor, two objects will point to the same memory. When one is destroyed, the other holds a dangling pointer. The canonical form ensures each object manages its own copy of resources.

### Operator Overloading Rules

- **Member functions**: When the left operand is the class type (`Fixed a; a + b;`)
- **Non-member functions**: When the left operand is not the class type (`std::cout << a;`)
- **Return types matter**: Comparison operators return `bool`; arithmetic operators return a new object; pre-increment returns a reference; post-increment returns a copy
- **Self-assignment check**: `operator=` should handle `a = a` gracefully

### Pre-increment vs Post-increment

```cpp
Fixed& operator++() {       // Pre: modify, return reference (efficient)
    value++;
    return *this;
}

Fixed operator++(int) {      // Post: copy, modify, return old copy (extra copy)
    Fixed temp = *this;
    value++;
    return temp;
}
```

The `int` parameter in `operator++(int)` is a dummy — it exists only to distinguish post-increment from pre-increment at the syntactic level.

## Compilation

```bash
cd ex00 && make && ./Fixed
cd ex01 && make && ./Fixed
cd ex02 && make && ./Fixed
```

## Key Takeaways

- The Orthodox Canonical Form prevents resource management bugs in copied objects
- Operator overloading makes user-defined types feel native to the language
- Fixed-point arithmetic provides fractional precision without floating-point hardware
- Pre-increment (`++i`) is more efficient than post-increment (`i++`) because it avoids creating a temporary copy
- Non-member `operator<<` enables stream insertion for custom types
