#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
}

Intern::Intern(const Intern&)
{
}

Intern& Intern::operator=(const Intern&)
{
    return *this;
}

Intern::~Intern()
{
}

AForm* Intern::makeForm(const std::string& formName, const std::string& target) const
{
    const std::string names[3] = {
        "shrubbery creation",
        "robotomy request",
        "presidential pardon"
    };

    for (int i = 0; i < 3; i++)
    {
        if (formName == names[i])
        {
            AForm* form = NULL;
            if (i == 0)
                form = new ShrubberyCreationForm(target);
            else if (i == 1)
                form = new RobotomyRequestForm(target);
            else
                form = new PresidentialPardonForm(target);
            std::cout << "Intern creates " << formName << std::endl;
            return form;
        }
    }
    std::cout << "Intern: form \"" << formName << "\" does not exist." << std::endl;
    return NULL;
}
