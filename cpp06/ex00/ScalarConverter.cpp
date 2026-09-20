#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter &other)
{
  (void)other;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other)
{
  (void)other;
  return *this;
}

ScalarConverter::~ScalarConverter()
{
}
void ScalarConverter::convert(std::string to_convert)
{
    if (to_convert.empty())
    {
        std::cout << "no string provided" << std::endl;
        return;
    }
    if (to_convert.size() == 1 && !isdigit(to_convert[0]))
    {
        char c = to_convert[0];
        std::cout << "char: '" << c << "'" << std::endl;
        std::cout << "int: " << static_cast<int>(c) << std::endl;
        std::cout << "float: " << static_cast<float>(c) << ".0f" << std::endl;
        std::cout << "double: " << static_cast<double>(c) << ".0" << std::endl;
        return;
    }
    char *str;
    double val = strtod(to_convert.c_str(), &str);
    if (*str && (*str != 'f' || *(str + 1)))
    {
        std::cout << "invalid input" << std::endl;
        return;
    }
    std::cout << "char: ";
    if (std::isnan(val) || std::isinf(val) || val < 0 || val > 127)
        std::cout << "impossible" << std::endl;
    else if (val < 32 || val == 127)
        std::cout << "Non displayable" << std::endl;
    else
        std::cout << "'" << static_cast<char>(val) << "'" << std::endl;
    std::cout << "int: ";
    if (std::isnan(val) || std::isinf(val) || val < INT_MIN || val > INT_MAX)
        std::cout << "impossible" << std::endl;
    else
        std::cout << static_cast<int>(val) << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(2) << static_cast<float>(val) << "f" << std::endl;
    std::cout << "double: " << val << std::endl;
}
