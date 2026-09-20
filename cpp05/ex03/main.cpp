#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    Intern intern;
    // Test 1: intern creates a robotomy request form
    AForm* form = intern.makeForm("robotomy request", "Bender");
    if (form)
    {
        Bureaucrat bob("Bob", 45);
        bob.signForm(*form);
        bob.executeForm(*form);
        delete form;
    }
    // Test 2: intern creates a shrubbery creation form
    form = intern.makeForm("shrubbery creation", "garden");
    if (form)
    {
        Bureaucrat alice("Alice", 137);
        alice.signForm(*form);
        alice.executeForm(*form);
        delete form;
    }
    // Test 3: intern creates a presidential pardon form
    form = intern.makeForm("presidential pardon", "Arthur");
    if (form)
    {
        Bureaucrat president("President", 5);
        president.signForm(*form);
        president.executeForm(*form);
        delete form;
    }
    return 0;
}
