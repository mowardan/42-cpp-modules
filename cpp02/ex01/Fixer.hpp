#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath>

class Fixed {
    int                 fixedPointValue;
    static const int    fractionalBits;

    public:
    Fixed();
    Fixed(const int intValue);
    Fixed(const float floatValue);
    Fixed(const Fixed& other);
    Fixed& operator=(const Fixed& other);
    ~Fixed();

    int toInt() const;
    float toFloat() const;
};

std::ostream& operator<<(std::ostream& os, const Fixed& obj);

#endif