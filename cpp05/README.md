# CPP05 — Exceptions and Bureaucratic Forms

## Overview

CPP05 introduces **exception handling** in C++ — the mechanism for reporting and recovering from runtime errors. Through a bureaucracy simulation, the module builds progressively from basic custom exceptions to a full class hierarchy with abstract base forms, concrete form types, and a factory pattern. This is the most architecturally complex module so far, combining inheritance, polymorphism, exceptions, and design patterns.

## Learning Objectives

- Exception handling (`try`/`catch`/`throw`)
- Custom exception classes inheriting from `std::exception`
- Nested classes (exceptions defined inside their owning class)
- Abstract base classes as interfaces
- Concrete derived classes with specialized behavior
- Factory pattern (Intern creating forms)
- Template Method pattern (base class controlling execution flow)

## Exercise Index

| Exercise | Name | Key Concepts | Description |
|----------|------|-------------|-------------|
| ex00 | Mommy, when I grow up, I want to be a bureaucrat! | Custom exceptions, grade validation | `Bureaucrat` with grade range [1, 150] |
| ex01 | Form up, maggots! | Exception propagation, class interaction | `Form` that requires minimum grade to sign |
| ex02 | No, you need form 28B, not 28C... | Abstract class, concrete forms | `AForm` base with 3 concrete form types |
| ex03 | At least this beats coffee-making | Factory pattern | `Intern` creates forms by name |

---

## ex00 — Bureaucrat

**Files:** `Bureaucrat.hpp`, `Bureaucrat.cpp`, `main.cpp`

A `Bureaucrat` has a constant name and a grade between 1 (highest) and 150 (lowest).

### Exception Design

```cpp
class Bureaucrat {
    const std::string name;
    int grade;   // 1 = highest, 150 = lowest

public:
    class GradeTooHighException : public std::exception {
        const char* what() const throw();  // Returns "Grade is too high!"
    };

    class GradeTooLowException : public std::exception {
        const char* what() const throw();  // Returns "Grade is too low!"
    };

    void incrementGrade();  // grade-- (numerically lower = higher rank)
    void decrementGrade();  // grade++
};
```

Exceptions are thrown when:
- Constructing with grade < 1 or > 150
- Incrementing past grade 1
- Decrementing past grade 150

### Stream Insertion

```cpp
std::ostream& operator<<(std::ostream& out, const Bureaucrat& b) {
    out << b.getName() << ", bureaucrat grade " << b.getGrade();
    return out;
}
```

---

## ex01 — Form

**Files:** `Bureaucrat.hpp/cpp`, `Form.hpp/cpp`, `main.cpp`

Introduces `Form` — a document that requires a minimum Bureaucrat grade to be signed.

### Form Class

```cpp
class Form {
    const std::string name;
    bool isSigned;
    const int gradeToSign;     // Minimum grade required to sign
    const int gradeToExecute;  // Minimum grade required to execute

public:
    void beSigned(const Bureaucrat& b);  // Throws if b.grade > gradeToSign
};
```

### Bureaucrat–Form Interaction

```cpp
void Bureaucrat::signForm(Form& form) {
    try {
        form.beSigned(*this);
        std::cout << getName() << " signed " << form.getName() << std::endl;
    } catch (std::exception& e) {
        std::cout << getName() << " couldn't sign " << form.getName()
                  << " because " << e.what() << std::endl;
    }
}
```

The Bureaucrat catches the exception internally and prints a meaningful message rather than letting it propagate.

---

## ex02 — Concrete Forms

**Files:** `AForm.hpp/cpp`, `Bureaucrat.hpp/cpp`, `ShrubberyCreationForm.hpp/cpp`, `RobotomyRequestForm.hpp/cpp`, `PresidentialPardonForm.hpp/cpp`, `main.cpp`

### AForm (Abstract Base)

`Form` is renamed to `AForm` and made abstract with a pure virtual `executeAction()`:

```cpp
class AForm {
protected:
    virtual void executeAction() const = 0;  // Derived classes implement this

public:
    void execute(Bureaucrat const& executor) const;  // Template Method
};
```

### Template Method Pattern

`AForm::execute()` controls the flow — checking preconditions before delegating to the concrete implementation:

```cpp
void AForm::execute(Bureaucrat const& executor) const {
    if (!isSigned)
        throw FormNotSignedException();
    if (executor.getGrade() > gradeToExecute)
        throw GradeTooLowException();
    executeAction();  // Concrete form does its specific work
}
```

### Concrete Forms

| Form | Sign Grade | Execute Grade | Action |
|------|-----------|--------------|--------|
| `ShrubberyCreationForm` | 145 | 137 | Writes ASCII trees to `<target>_shrubbery` file |
| `RobotomyRequestForm` | 72 | 45 | 50% chance of successful robotomy (uses `rand()`) |
| `PresidentialPardonForm` | 25 | 5 | Informs that target was pardoned by Zaphod Beeblebrox |

### Exception Hierarchy

```
std::exception
├── AForm::GradeTooHighException
├── AForm::GradeTooLowException
└── AForm::FormNotSignedException    ← New in ex02
```

---

## ex03 — Intern

**Files:** All ex02 files + `Intern.hpp`, `Intern.cpp`, `main.cpp`

### Factory Pattern

The `Intern` class creates forms by name without the caller needing to know the concrete type:

```cpp
AForm* Intern::makeForm(const std::string& formName, const std::string& target) const {
    const std::string names[3] = {
        "shrubbery creation", "robotomy request", "presidential pardon"
    };

    for (int i = 0; i < 3; i++) {
        if (formName == names[i]) {
            AForm* form = NULL;
            if (i == 0) form = new ShrubberyCreationForm(target);
            else if (i == 1) form = new RobotomyRequestForm(target);
            else form = new PresidentialPardonForm(target);
            std::cout << "Intern creates " << formName << std::endl;
            return form;
        }
    }
    std::cout << "Intern: form \"" << formName << "\" does not exist." << std::endl;
    return NULL;
}
```

Returns `NULL` for unknown form names rather than throwing. The caller is responsible for `delete`ing the returned form.

---

## Technical Concepts

### Exception Handling Flow

```
throw → stack unwinding → catch

try {
    bureaucrat.decrementGrade();  // Throws GradeTooLowException
    // Code after throw is NEVER reached
}
catch (const std::exception& e) {
    // Handle error — e.what() returns error message
    std::cout << e.what() << std::endl;
}
// Execution continues here after catch
```

When an exception is thrown:
1. The current function's remaining code is skipped
2. The stack unwinds — destructors for local objects are called
3. The nearest matching `catch` block handles the exception
4. If no `catch` matches, `std::terminate()` is called

### Custom Exception Classes

All exceptions inherit from `std::exception` and override `what()`:

```cpp
class GradeTooHighException : public std::exception {
public:
    const char* what() const throw() {
        return "Grade is too high!";
    }
};
```

The `throw()` specification after `what()` is a C++98 exception specification meaning "this function throws nothing."

### Nested Classes

Exception classes are defined **inside** the class they belong to:

```cpp
class Bureaucrat {
public:
    class GradeTooHighException : public std::exception { ... };
};

// Usage:
throw Bureaucrat::GradeTooHighException();
```

This scoping ties the exception semantically to its source and avoids polluting the global namespace.

### Design Pattern Summary

| Pattern | Where | Purpose |
|---------|-------|---------|
| **Template Method** | `AForm::execute()` | Base controls flow, derived provides behavior |
| **Factory** | `Intern::makeForm()` | Creates objects without exposing concrete types |
| **Strategy** (via inheritance) | Concrete forms | Same interface, different actions |

## Compilation

```bash
cd ex00 && make && ./Bureaucrat
cd ex01 && make && ./Form
cd ex02 && make && ./AForm
cd ex03 && make && ./Intern
```

## Key Takeaways

- Exceptions separate error reporting from error handling — cleaner than return codes
- Custom exception classes with `what()` provide meaningful error messages
- The Template Method pattern lets base classes enforce preconditions while derived classes provide behavior
- Factory methods decouple object creation from the code that uses those objects
- `const std::string` members require initialization lists — they cannot be assigned after construction
