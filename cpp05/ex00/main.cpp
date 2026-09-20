#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat b("Bazghoro", 150);
        b.decrementGrade();
    }
    catch (const std::exception& e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    return 0;
}