# CPP00 — C++ Fundamentals

## Overview

CPP00 introduces the basic building blocks of C++ programming: namespaces, classes, member functions, I/O streams, and formatted output. This module transitions from C-style procedural programming to C++ object-oriented design by implementing practical programs that use classes to encapsulate data and behavior.

## Learning Objectives

- Standard I/O with `std::cout`, `std::cin`, `std::endl`
- String manipulation with `std::string`
- Class declaration with private attributes and public methods
- Member function implementation
- Static arrays of objects
- Formatted output with `std::setw` and `std::iomanip`
- Input handling with `std::getline`

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Megaphone | I/O streams, character manipulation | Converts command-line arguments to uppercase |
| ex01 | My Awesome PhoneBook | Classes, encapsulation, formatted I/O | Interactive phonebook with add/search/exit commands |

---

## ex00 — Megaphone

**Files:** `megaphone.cpp`, `Makefile`

A simple program that takes command-line arguments and outputs them in uppercase. If no arguments are given, it prints a default noise message.

### Implementation Details

- Iterates through each character of each argument
- Converts lowercase letters (`a-z`) to uppercase by subtracting 32 (ASCII offset)
- Handles multiple arguments by concatenating output
- Uses raw character manipulation rather than `std::toupper`

```bash
./megaphone "shhh... I think the students are asleep..."
# Output: SHHH... I THINK THE STUDENTS ARE ASLEEP...

./megaphone
# Output: * LOUD AND UNBEARABLE FEEDBACK NOISE *
```

---

## ex01 — My Awesome PhoneBook

**Files:** `main.cpp`, `PhoneBook.hpp`, `PhoneBook.cpp`, `Contact.hpp`, `Contact.cpp`, `Makefile`

An interactive phonebook application that stores up to 8 contacts in memory. The program accepts three commands: `ADD`, `SEARCH`, and `EXIT`.

### Class Design

```
PhoneBook
├── Contact contacts[8]    (fixed-size array)
├── int next_index         (circular insertion index)
├── int count              (number of stored contacts)
├── core()                 (main command loop)
├── add_contact()          (create and store a contact)
└── display_element()      (formatted table display + detail view)

Contact
├── string name            (private)
├── string last_name       (private)
├── string nick_name       (private)
├── string phone_number    (private)
├── string darkest_secret  (private)
├── set_element()          (prompt user for all fields)
├── get()                  (print all fields)
├── checktheelemts()       (validate no empty fields)
├── getName()              (getter)
├── getLastName()          (getter)
└── getNickName()          (getter)
```

### Key Design Decisions

- **Circular buffer**: When all 8 slots are full, new contacts overwrite the oldest entry using modular arithmetic (`next_index = (next_index + 1) % 8`)
- **No dynamic allocation**: The phonebook uses a fixed-size array — no `new` or `delete` needed
- **Formatted display**: Uses `std::setw(10)` for column-aligned output, with a `truncate()` function that abbreviates strings longer than 10 characters with a trailing dot
- **Input validation**: Empty fields are rejected with an error message; EOF handling via `std::getline` return checks
- **Recursive command loop**: The `core()` method calls itself recursively for the command loop

### Technical Concepts

#### Encapsulation

The `Contact` class keeps all data members private. External code accesses contact information only through getter methods (`getName()`, `getLastName()`, `getNickName()`) and the `get()` display method. This prevents direct modification of contact data after creation.

#### Stack-Allocated Objects

The entire phonebook exists on the stack — `PhoneBook` contains a fixed array of `Contact` objects. When the program exits, all memory is automatically reclaimed. This contrasts with the heap allocation patterns introduced in CPP01.

#### Formatted Output with `<iomanip>`

The `display_element()` method uses `std::setw(10)` to create uniform column widths in the contact table. The static `truncate()` function ensures no field exceeds the column width:

```cpp
static std::string truncate(std::string str) {
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}
```

## Compilation

```bash
# ex00
cd ex00 && make && ./megaphone "test"

# ex01
cd ex01 && make && ./PhoneBook
```

## Key Takeaways

- C++ classes encapsulate data and provide controlled access through public interfaces
- `std::string` eliminates manual memory management for text compared to C-style `char*`
- Formatted I/O with `<iomanip>` enables professional output presentation
- Fixed-size containers avoid heap allocation but impose capacity limits
- Input validation is essential for interactive programs
