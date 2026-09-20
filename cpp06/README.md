# CPP06 — C++ Type Casting

## Overview

CPP06 introduces the C++ type casting system — a set of four explicit cast operators that replace the dangerous, catch-all C-style cast `(type)value`. Each exercise focuses on a specific cast operator and the problem it solves, progressing from compile-time conversions to raw memory reinterpretation to runtime type identification.

In C, casting with `(type)value` is easy but dangerous: the compiler won't stop fundamentally unsafe conversions, and finding `(int)` in a large codebase is nearly impossible. C++ replaces this with four named operators, each with a clear purpose and searchable syntax.

## Learning Objectives

- `static_cast` — compile-time checked conversions between related types
- `reinterpret_cast` — raw memory reinterpretation between unrelated types
- `dynamic_cast` — runtime type identification for polymorphic hierarchies
- Non-instantiable utility classes (private constructor pattern)
- `uintptr_t` and pointer-to-integer conversions
- RTTI (Run-Time Type Information) and virtual tables

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Conversion of scalar types | `static_cast`, string parsing | Convert string literal to char, int, float, double |
| ex01 | Serialization | `reinterpret_cast`, `uintptr_t` | Serialize/deserialize pointers to integers |
| ex02 | Identify real type | `dynamic_cast`, RTTI | Identify derived type through base pointer/reference |

---

## ex00 — ScalarConverter

**Files:** `ScalarConverter.hpp`, `ScalarConverter.cpp`, `main.cpp`

### What is `static_cast`?

`static_cast` performs compile-time type checks. It converts between related types — `int` to `float`, `char` to `double`, `enum` to `int`. If the conversion is nonsensical (e.g., `float` to `std::string`), the compiler refuses. This makes it fundamentally safer than C-style casts.

```cpp
double val = 42.5;
int i = static_cast<int>(val);     // OK: 42 (truncates)
char c = static_cast<char>(val);   // OK: '*' (ASCII 42)
```

### Implementation

`ScalarConverter` is a non-instantiable utility class (private constructor) with a single static method:

```cpp
class ScalarConverter {
private:
    ScalarConverter();  // Cannot instantiate
public:
    static void convert(std::string str);
};
```

The `convert()` method:
1. Handles single non-digit characters as `char` type directly
2. Parses numeric strings using `strtod()` to get a `double`
3. Validates the parse result (checks for trailing characters, allows `f` suffix)
4. Displays conversions to all four scalar types with appropriate edge-case handling

### Edge Cases Handled

- **Pseudo-literals**: `nan`, `inf`, `+inf`, `-inf`, `nanf`, `inff` — valid for float/double, impossible for char/int
- **Non-displayable chars**: Values 0–31 and 127 are printed as "Non displayable"
- **Overflow**: Values outside `INT_MIN`–`INT_MAX` range print "impossible" for `int`
- **Empty input**: Prints an error message

---

## ex01 — Serializer

**Files:** `Serializer.hpp`, `Serializer.cpp`, `Data.hpp`, `main.cpp`

### What is `reinterpret_cast`?

`reinterpret_cast` tells the compiler: "Take these exact bits in memory and treat them as this other type." It doesn't convert values — it reinterprets raw memory. This is the most dangerous cast and should only be used in low-level systems programming.

```cpp
Data* ptr = &someData;
uintptr_t raw = reinterpret_cast<uintptr_t>(ptr);  // Address → integer
Data* back = reinterpret_cast<Data*>(raw);          // Integer → address
// ptr == back (same address)
```

### Implementation

```cpp
struct Data {
    int id;
    std::string name;
};

class Serializer {
private:
    Serializer();  // Non-instantiable
public:
    static uintptr_t serialize(Data* ptr);
    static Data* deserialize(uintptr_t raw);
};
```

`uintptr_t` (from `<stdint.h>`) is an unsigned integer type guaranteed to be large enough to hold a pointer on any architecture. The main function verifies the round-trip: serialize → deserialize produces the original pointer, and all data members are intact.

### Practical Use

Serialization of pointers to integers appears in:
- Network programming (sending object references as IDs)
- Inter-process communication
- Hardware interfaces and memory-mapped I/O
- Hash table implementations

---

## ex02 — Type Identification

**Files:** `Base.hpp`, `Base.cpp`, `A.hpp`, `B.hpp`, `C.hpp`, `main.cpp`

### What is `dynamic_cast`?

`dynamic_cast` is the only cast that operates at **runtime**. It inspects the actual type of a polymorphic object by examining its vtable, regardless of the pointer/reference type used to hold it.

**Requirement**: The base class must have at least one virtual function (typically the destructor) to generate RTTI.

### Implementation

A base class with three empty derived classes:

```cpp
class Base { public: virtual ~Base(); };
class A : public Base {};
class B : public Base {};
class C : public Base {};
```

`generate()` randomly creates A, B, or C and returns a `Base*`. Two `identify()` functions determine the actual type:

### Pointer Identification

```cpp
void identify(Base* p) {
    if (dynamic_cast<A*>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p))
        std::cout << "C" << std::endl;
}
```

When `dynamic_cast` fails on a **pointer**, it returns `NULL`.

### Reference Identification

```cpp
void identify(Base& p) {
    try { (void)dynamic_cast<A&>(p); std::cout << "A" << std::endl; return; }
    catch (...) {}
    try { (void)dynamic_cast<B&>(p); std::cout << "B" << std::endl; return; }
    catch (...) {}
    try { (void)dynamic_cast<C&>(p); std::cout << "C" << std::endl; return; }
    catch (...) {}
}
```

When `dynamic_cast` fails on a **reference**, it **throws `std::bad_cast`** — because references cannot be null. Each attempt is wrapped in try/catch to cascade through the types.

---

## Technical Concepts

### Cast Comparison

| Cast | Check Time | Safety | Use Case |
|------|-----------|--------|----------|
| `static_cast` | Compile-time | Safe for related types | Numeric conversions, upcasting |
| `reinterpret_cast` | None | Unsafe | Pointer ↔ integer, unrelated pointer types |
| `dynamic_cast` | Runtime | Safe | Downcasting in polymorphic hierarchies |
| `const_cast` | Compile-time | Moderate | Adding/removing const qualifier |

### Why Not C-Style Casts?

```cpp
// C-style: which cast is this? No way to tell.
int* p = (int*)someVoidPointer;

// C++ style: explicit intent, searchable, compiler-checked
int* p = reinterpret_cast<int*>(someVoidPointer);
```

C-style casts try each C++ cast in order (`const_cast`, `static_cast`, `reinterpret_cast`) and use the first one that compiles. This means a seemingly safe cast might silently become a `reinterpret_cast` when code changes.

### Non-Instantiable Utility Classes

Both `ScalarConverter` and `Serializer` use the same pattern:

```cpp
class Utility {
private:
    Utility();                         // No construction
    Utility(const Utility&);           // No copying
    Utility& operator=(const Utility&); // No assignment
    ~Utility();                        // No destruction
public:
    static void doSomething();  // Only static methods
};
```

This is the C++98 equivalent of `= delete` in C++11. It ensures the class serves only as a namespace for its static methods.

## Compilation

```bash
cd ex00 && make && ./ScalarConverter 42.0f
cd ex01 && make && ./Serializer
cd ex02 && make && ./Identify
```

## Key Takeaways

- Use `static_cast` for safe, compile-time checked conversions between related types
- Use `reinterpret_cast` only for raw memory operations — it bypasses all type safety
- Use `dynamic_cast` to safely downcast in polymorphic hierarchies — it's the only runtime cast
- `dynamic_cast` on pointers returns `NULL` on failure; on references, it throws `std::bad_cast`
- Named casts are searchable, self-documenting, and compiler-checked — always prefer them over C-style casts
