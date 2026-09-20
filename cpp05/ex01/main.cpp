#include "Bureaucrat.hpp"
#include "Form.hpp"
#include <iostream>

int main()
{
    try
    {
        Bureaucrat b("BAzghoro", 50);
        Form e("Form", 50, 50);
        std::cout << e << std::endl;
        e.beSigned(b);
        std::cout << "Result: " << e << std::endl;
    }
    catch (std::exception &e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}