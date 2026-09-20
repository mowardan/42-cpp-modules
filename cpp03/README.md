# CPP03 — Inheritance

## Overview

CPP03 introduces **inheritance** in C++, one of the three pillars of object-oriented programming. Through a game-inspired class hierarchy (`ClapTrap` → `ScavTrap` → `FragTrap`), the module demonstrates how derived classes extend base classes, how constructors and destructors chain through the hierarchy, and how derived classes can override base class behavior.

## Learning Objectives

- Single inheritance (`class Derived : public Base`)
- `protected` access specifier (shared with derived classes, hidden from external code)
- Constructor and destructor chaining (base constructed first, destroyed last)
- Initialization lists for base class constructors
- Function hiding (derived class redefining a base class method)
- Extending class functionality through inheritance

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Aaaaand... OPEN! | Base class design | Implement `ClapTrap` with attack, damage, and repair |
| ex01 | Serena, my love! | Single inheritance | Add `ScavTrap` inheriting from `ClapTrap` |
| ex02 | Repetitive work | Multi-level hierarchy | Add `FragTrap` inheriting from `ClapTrap` |

---

## ex00 — ClapTrap

**Files:** `ClapTrap.hpp`, `ClapTrap.cpp`, `main.cpp`

The base class for all exercises. `ClapTrap` is a game character with attributes and actions:

### Attributes

| Attribute | Type | Default | Purpose |
|-----------|------|---------|---------|
| `name` | `std::string` | constructor param | Character identifier |
| `hitpoints` | `unsigned int` | 10 | Health — actions require `> 0` |
| `energy_points` | `unsigned int` | 10 | Energy — attack/repair cost 1 each |
| `attack_damage` | `unsigned int` | 0 | Damage dealt per attack |

### Actions

- **`attack(target)`**: Costs 1 energy, prints damage dealt
- **`takeDamage(amount)`**: Reduces hitpoints, prints destruction if health reaches 0
- **`beRepaired(amount)`**: Costs 1 energy, increases hitpoints

All actions check for sufficient energy and hitpoints before executing. The class follows the Orthodox Canonical Form with full constructor/copy/assignment/destructor implementations.

---

## ex01 — ClapTrap + ScavTrap

**Files:** `ClapTrap.hpp/cpp`, `ScavTrap.hpp/cpp`, `main.cpp`

### Key Change: `private` → `protected`

In ex00, ClapTrap's attributes are `private`. In ex01, they become `protected` so that `ScavTrap` can access them directly:

```cpp
class ClapTrap {
protected:    // Changed from private — accessible to derived classes
    std::string name;
    unsigned int hitpoints;
    unsigned int energy_points;
    unsigned int attack_damage;
};
```

### ScavTrap

```cpp
class ScavTrap : public ClapTrap {
public:
    ScavTrap();
    ScavTrap(std::string name);
    ~ScavTrap();

    void attack(const std::string& target);  // Overrides ClapTrap::attack
    void guardGate();                         // Unique to ScavTrap
};
```

`ScavTrap` inherits from `ClapTrap` and:
- Calls the base class constructor via initialization list: `ScavTrap(name) : ClapTrap(name)`
- **Hides** the base class `attack()` with its own version that prints "ScavTrap" instead of "ClapTrap"
- Adds `guardGate()` — a method unique to ScavTrap

### Construction/Destruction Order

```
Creating ScavTrap "krawisa":
  1. ClapTrap krawisa constructed.     ← Base first
  2. ScavTrap krawisa constructed.     ← Derived second

Destroying ScavTrap "krawisa":
  1. ScavTrap krawisa destructed.      ← Derived first
  2. ClapTrap krawisa destructed.      ← Base last
```

This ordering is fundamental: the base is always fully constructed before the derived class runs, and the derived class is always fully destroyed before the base destructor runs.

---

## ex02 — ClapTrap + ScavTrap + FragTrap

**Files:** `ClapTrap.hpp/cpp`, `ScavTrap.hpp/cpp`, `FragTrap.hpp/cpp`, `main.cpp`

Adds a second derived class, `FragTrap`, with its own unique ability:

```cpp
class FragTrap : public ClapTrap {
public:
    FragTrap();
    FragTrap(std::string name);
    ~FragTrap();

    void highFivesGuys(void);  // Unique to FragTrap
};
```

### Class Hierarchy

```
        ClapTrap
       /        \
  ScavTrap    FragTrap
```

Both `ScavTrap` and `FragTrap` independently inherit from `ClapTrap`. They share the same base attributes and behavior but add their own specializations:

| Class | Unique Method | Behavior |
|-------|--------------|----------|
| `ScavTrap` | `guardGate()` | Enters Gate Keeper mode |
| `FragTrap` | `highFivesGuys()` | Requests a high five |

---

## Technical Concepts

### Access Specifiers in Inheritance

| Specifier | Within class | Derived classes | External code |
|-----------|-------------|-----------------|---------------|
| `private` | ✓ | ✗ | ✗ |
| `protected` | ✓ | ✓ | ✗ |
| `public` | ✓ | ✓ | ✓ |

The shift from `private` to `protected` in ex01 is deliberate: it allows derived classes to directly access base class data without requiring getters/setters, while still hiding that data from external code.

### Function Hiding vs Virtual Override

In this module, `ScavTrap::attack()` **hides** `ClapTrap::attack()` rather than overriding it virtually:

```cpp
ClapTrap* ptr = new ScavTrap("test");
ptr->attack("target");  // Calls ClapTrap::attack — NOT ScavTrap::attack
```

This is because `ClapTrap::attack()` is not declared `virtual`. True polymorphic dispatch (where the derived version is called through a base pointer) is introduced in CPP04.

### Constructor Delegation

Derived constructors must initialize their base class:

```cpp
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    // ClapTrap(name) is already fully constructed here
    std::cout << "ScavTrap " << name << " constructed." << std::endl;
}
```

If no base constructor is specified, the compiler implicitly calls the base default constructor.

### Common Interview Questions

- **What order are constructors/destructors called in inheritance?** Base constructor first → derived constructor. Derived destructor first → base destructor.
- **What is the difference between `private` and `protected`?** `protected` members are accessible in derived classes; `private` members are not.
- **What is function hiding?** When a derived class declares a function with the same name as a base class function (without `virtual`), the base function is hidden, not overridden.

## Compilation

```bash
cd ex00 && make && ./ClapTrap
cd ex01 && make && ./ScavTrap
cd ex02 && make && ./FragScavTrap
```

## Key Takeaways

- Inheritance enables code reuse — `ScavTrap` and `FragTrap` share `ClapTrap`'s attributes and logic
- `protected` provides a middle ground between `private` (too restrictive for inheritance) and `public` (too open)
- Construction order is base → derived; destruction order is derived → base
- Without `virtual`, calling a method through a base pointer invokes the base version, not the derived version
