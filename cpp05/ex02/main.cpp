#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    // Test ShrubberyCreationForm
    try
    {
        Bureaucrat alice("Alice", 137);
        ShrubberyCreationForm shrub("home");
        std::cout << shrub << std::endl;
        alice.signForm(shrub);
        alice.executeForm(shrub);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    // Test RobotomyRequestForm
    try
    {
        Bureaucrat bob("Bob", 45);
        RobotomyRequestForm robot("Target");
        std::cout << robot << std::endl;
        bob.signForm(robot);
        bob.executeForm(robot);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    // Test PresidentialPardonForm
    try
    {
        Bureaucrat president("President", 25);
        PresidentialPardonForm pardon("Criminal");
        std::cout << pardon << std::endl;
        president.signForm(pardon);
        president.executeForm(pardon);
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
