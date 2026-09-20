# CPP04 — Polymorphism and Abstract Classes

## Overview

CPP04 is the culmination of the object-oriented programming foundation. It introduces **runtime polymorphism** through virtual functions, demonstrates the critical importance of **virtual destructors**, explores **deep copy** semantics with dynamically allocated members, and concludes with **abstract classes** that prevent direct instantiation of base types.

## Learning Objectives

- Virtual functions and runtime polymorphism (vtable dispatch)
- Virtual destructors (preventing memory leaks in polymorphic hierarchies)
- Deep copy vs shallow copy with dynamically allocated members
- Abstract classes and pure virtual functions (`= 0`)
- Demonstrating incorrect polymorphism (WrongAnimal/WrongCat)

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Polymorphism | `virtual` functions, correct vs wrong polymorphism | Animal hierarchy with virtual `makeSound()` |
| ex01 | I don't want to set the world on fire | Deep copy, composition | Add `Brain*` to Dog/Cat with proper copy semantics |
| ex02 | Abstract class | Pure virtual functions, `= 0` | Make `Animal` abstract — uninstantiable |

---

## ex00 — Polymorphism

**Files:** `Animal.hpp/cpp`, `Cat.hpp/cpp`, `Dog.hpp/cpp`, `WrongAnimal.hpp/cpp`, `WrongCat.hpp/cpp`, `main.cpp`

### Correct Polymorphism

```cpp
class Animal {
protected:
    std::string type;
public:
    virtual ~Animal();              // Virtual destructor
    virtual void makeSound() const; // Virtual — enables polymorphism
    std::string getType() const;
};

class Cat : public Animal {
public:
    void makeSound() const;  // Overrides Animal::makeSound
};
```

With `virtual`, calling `makeSound()` through a base pointer invokes the **derived** implementation:

```cpp
const Animal* i = new Cat();
i->makeSound();  // Prints "Miaw" — Cat's version
delete i;         // Calls Cat destructor, then Animal destructor
```

### Incorrect Polymorphism (WrongAnimal)

`WrongAnimal` deliberately omits `virtual` on `makeSound()`:

```cpp
class WrongAnimal {
public:
    void makeSound() const;  // NOT virtual
};

const WrongAnimal* wrongCat = new WrongCat();
wrongCat->makeSound();  // Prints "WrongAnimal makes a sound" — base version!
```

Without `virtual`, the compiler uses the **static type** (WrongAnimal*) to determine which function to call, ignoring the actual object type.

### Virtual Destructor

The `Animal` destructor is declared `virtual` to ensure that when deleting through a base pointer, the derived destructor runs first:

```cpp
const Animal* j = new Dog();
delete j;  // Without virtual ~Animal(): ONLY Animal destructor runs → memory leak
           // With virtual ~Animal(): Dog destructor runs first, then Animal
```

---

## ex01 — Deep Copy with Brain

**Files:** `Animal.hpp/cpp`, `Brain.hpp/cpp`, `Cat.hpp/cpp`, `Dog.hpp/cpp`, `main.cpp`

### Brain Class

```cpp
class Brain {
    std::string ideas[100];  // Array of 100 idea strings
public:
    Brain();
    Brain(const Brain& other);  // Deep copies all 100 ideas
    Brain& operator=(const Brain& other);
    ~Brain();
};
```

### Composition with Ownership

`Cat` and `Dog` now contain a `Brain*` — a pointer to a heap-allocated Brain:

```cpp
class Cat : public Animal {
    Brain* brain;   // Owned resource — Cat is responsible for lifetime
public:
    Cat();           // brain = new Brain()
    Cat(const Cat&); // brain = new Brain(*(other.brain))  ← deep copy
    Cat& operator=(const Cat&);  // delete brain; brain = new Brain(...)
    virtual ~Cat();  // delete brain
};
```

### Why Deep Copy Matters

Without deep copy, copying a `Cat` would copy the **pointer** — two Cat objects pointing to the same Brain:

```
Shallow copy (wrong):
  Cat A → brain* ──→ [Brain object]
  Cat B → brain* ──↗

  delete A → frees Brain
  delete B → double-free! Undefined behavior.
```

```
Deep copy (correct):
  Cat A → brain* ──→ [Brain object 1]
  Cat B → brain* ──→ [Brain object 2]  ← independent copy

  delete A → frees Brain 1
  delete B → frees Brain 2  ✓
```

The copy constructor allocates a **new** Brain and copies the contents. The assignment operator deletes the old Brain before allocating a new one.

---

## ex02 — Abstract Class

**Files:** `Animal.hpp/cpp`, `Brain.hpp/cpp`, `Cat.hpp/cpp`, `Dog.hpp/cpp`, `main.cpp`

### The Change

One line changes `Animal` from a concrete class to an abstract class:

```cpp
// ex01:
virtual void makeSound() const;       // Has a default implementation

// ex02:
virtual void makeSound() const = 0;   // Pure virtual — no implementation
```

### Effect

```cpp
Animal a;             // COMPILE ERROR — cannot instantiate abstract class
const Animal* c = new Cat();  // OK — Cat provides makeSound() implementation
```

An abstract class serves as an **interface contract**: any class inheriting from `Animal` must implement `makeSound()`, or it too becomes abstract.

Note that `Animal` still has a constructor and destructor — abstract classes can have state and implemented methods. Only the pure virtual function(s) prevent direct instantiation.

---

## Technical Concepts

### How Virtual Functions Work (vtable)

When a class has virtual functions, the compiler creates a **virtual table** (vtable) — an array of function pointers:

```
Animal vtable:          Cat vtable:
┌──────────────┐       ┌──────────────┐
│ ~Animal()    │       │ ~Cat()       │
│ makeSound()  │──→default  │ makeSound()  │──→ "Miaw"
└──────────────┘       └──────────────┘
```

Each object contains a hidden pointer (vptr) to its class's vtable. When you call `ptr->makeSound()`, the runtime follows the vptr to the correct vtable and calls the function there — not the function determined by the pointer type.

**Cost**: One pointer per object (vptr) + one table per class (vtable). This is why virtual functions have slight overhead compared to non-virtual calls.

### The Rule of Three

If a class manages a resource (like `Brain*`), it must implement:
1. **Destructor** — to release the resource
2. **Copy constructor** — to create an independent copy
3. **Copy assignment operator** — to release the old resource and copy the new one

If any one of these is needed, all three are likely needed. This is the **Rule of Three** in C++.

### Abstract Class vs Interface

| Feature | Abstract Class | Pure Interface |
|---------|---------------|----------------|
| Pure virtual methods | At least one | All methods |
| Implemented methods | Can have | None |
| Member variables | Can have | None (conventionally) |
| Constructor | Can have | Typically not |

C++ does not have a dedicated `interface` keyword. Abstract classes with only pure virtual methods serve the same purpose.

## Compilation

```bash
cd ex00 && make && ./Animal
cd ex01 && make && ./Brain
cd ex02 && make && ./Abstract
```

## Key Takeaways

- `virtual` enables runtime polymorphism — the actual object type determines which function runs
- Virtual destructors are **mandatory** for any class used polymorphically with `delete` through a base pointer
- Deep copy is essential when classes own heap-allocated resources — shallow copy leads to double-free
- Pure virtual functions (`= 0`) make a class abstract and enforce that derived classes implement the interface
- The WrongAnimal example concretely demonstrates what breaks without `virtual`
