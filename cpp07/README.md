# CPP07 — Templates

## Overview

CPP07 introduces **templates** — C++'s mechanism for writing type-independent code. Templates allow functions and classes to operate on any data type without being rewritten for each one. The compiler generates the appropriate specialized code at compile time, providing the performance of hand-written type-specific code with the flexibility of generic programming.

## Learning Objectives

- Function templates (type-parameterized free functions)
- Template argument deduction (compiler infers types from arguments)
- Class templates (type-parameterized classes)
- Template instantiation (how the compiler generates code)
- Const and non-const overloads in template context
- Exception handling within templated classes

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Start with a few functions | Function templates | Generic `swap`, `min`, `max` |
| ex01 | Iter | Function template with callable parameter | Apply a function to each element of an array |
| ex02 | Array | Class template | Generic dynamic array with bounds checking |

---

## ex00 — Function Templates (swap, min, max)

**Files:** `whatever.hpp`, `main.cpp`

Three function templates that work with any type supporting comparison and assignment:

```cpp
template <typename T>
void swap(T& a, T& b) {
    T tmp = a;
    a = b;
    b = tmp;
}

template <typename T>
T min(T& a, T& b) {
    if (b <= a) return b;
    else return a;
}

template <typename T>
T max(T& a, T& b) {
    if (a >= b) return a;
    else return b;
}
```

### Template Argument Deduction

The compiler infers `T` from the arguments:

```cpp
int a = 2, b = 3;
::swap(a, b);         // T deduced as int
std::string c = "chaine1", d = "chaine2";
::swap(c, d);         // T deduced as std::string
```

No explicit `<int>` or `<std::string>` specification needed — the compiler matches the argument types.

### Tie-Breaking

`min` returns `b` when values are equal (`b <= a`), and `max` returns `a` when values are equal (`a >= b`). This matches the 42 subject requirement that when arguments are equal, the second one is returned for `min` and the first for `max`.

---

## ex01 — iter

**Files:** `iter.hpp`, `main.cpp`

A function template that applies a callable to each element of an array:

```cpp
template <typename T, typename U>
void iter(T* arr, size_t len, U function) {
    for (size_t i = 0; i < len; i++)
        function(arr[i]);
}

// Const overload — for const arrays
template <typename T, typename U>
void iter(const T* arr, size_t len, U function) {
    for (size_t i = 0; i < len; i++)
        function(arr[i]);
}
```

### Two Template Parameters

Using separate template parameters `T` and `U` allows the callable (`U`) to be:
- A regular function pointer: `void print(const int& a)`
- A function that modifies elements: `void to_upper(std::string& str)`

### Const Overload

The second overload accepts `const T*`, enabling iteration over const arrays. Without this, passing a `const int[]` would fail to compile because the non-const version would try to bind a non-const pointer to a const array.

```cpp
const int arr2[5] = {1, 2, 3, 4, 5};
iter(arr2, 5, print);  // Uses const overload
```

---

## ex02 — Array (Class Template)

**Files:** `Array.hpp`, `main.cpp`

A fully generic dynamic array class template:

```cpp
template <typename T>
class Array {
private:
    T* array;
    size_t array_size;

public:
    Array();                          // Empty array (nullptr, size 0)
    Array(unsigned int n);            // Array of n value-initialized elements
    Array(const Array& other);        // Deep copy
    ~Array();                         // delete[]
    Array& operator=(const Array& other);  // Deep copy assignment

    T& operator[](size_t index);            // Bounds-checked access
    const T& operator[](size_t index) const; // Const bounds-checked access
    size_t size() const;
};
```

### Key Design Decisions

**Value Initialization**: `new T[n]()` — the parentheses ensure elements are value-initialized (zero for primitives, default-constructed for objects).

**Bounds Checking**: Both `operator[]` overloads throw `std::out_of_range` if the index exceeds `array_size`:

```cpp
T& operator[](size_t index) {
    if (index >= array_size)
        throw std::out_of_range("Index out of range");
    return array[index];
}
```

**Deep Copy**: The copy constructor and assignment operator allocate new memory and copy each element individually, preventing the shared-pointer problem.

**Const Correctness**: Two `operator[]` overloads — one returns `T&` (allows modification), one returns `const T&` (for const Array objects).

### Usage

```cpp
Array<int> arr(5);
for (size_t i = 0; i < arr.size(); i++)
    arr[i] = i + 1;  // 1, 2, 3, 4, 5

Array<std::string> strArr(3);
strArr[0] = "Hello";

try {
    std::cout << arr[10];  // Throws std::out_of_range
} catch (const std::out_of_range& e) {
    std::cerr << e.what() << std::endl;
}
```

---

## Technical Concepts

### How Templates Work

Templates are not compiled directly. Instead, the compiler generates a **specialization** for each unique type combination used:

```
Source code:        Array<int> a;    Array<std::string> b;

Compiler generates: class Array_int { int* array; ... };
                    class Array_string { std::string* array; ... };
```

This is called **template instantiation**. It happens at compile time, producing zero runtime overhead compared to hand-written type-specific classes.

### Template Code Organization

Templates must be defined in header files (or at least visible at the point of instantiation). This is because the compiler needs the full definition to generate specializations. Placing template implementations in `.cpp` files causes linker errors.

The exercises in this module keep all template code in `.hpp` files for this reason.

### Function Template vs Class Template

| Feature | Function Template | Class Template |
|---------|-------------------|----------------|
| **Deduction** | Arguments types auto-deduced | Must specify `<T>` explicitly (C++98) |
| **Syntax** | `template <typename T> T min(T&, T&)` | `template <typename T> class Array { ... }` |
| **Instantiation** | `min(a, b)` — implicit | `Array<int> a(5)` — explicit |
| **Specialization** | Per function | Per class |

### Trade-offs

- **Advantage**: Zero runtime overhead — templates are resolved at compile time
- **Advantage**: Type safety — the compiler checks that operations used in the template exist for the given type
- **Cost**: Longer compile times (each instantiation generates new code)
- **Cost**: Larger binary size (separate code generated for each type)
- **Cost**: Error messages can be cryptic (especially with nested templates)

## Compilation

```bash
cd ex00 && make && ./whatever
cd ex01 && make && ./iter
cd ex02 && make && ./Array
```

## Key Takeaways

- Templates enable writing type-independent code that is compiled into type-specific optimized code
- Function templates deduce types from arguments; class templates require explicit type parameters
- Template code must be in headers because the compiler needs the full definition at instantiation
- Class templates with dynamic memory must implement the Rule of Three (copy, assign, destroy) for each instantiation
- Const overloads on `operator[]` enable safe read-only access for const objects
