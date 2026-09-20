#ifndef   SPAN_HPP
# define  SPAN_HPP

#include <algorithm>
#include <exception>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <limits>

class Span
{
    private:
        unsigned int N;
        std::vector<int> numbers;

    public:
        Span(unsigned int n);
        Span(const Span &other);
        ~Span();
        Span &operator=(const Span &other);

        void addNumber(int number);
        int shortestSpan() const;
        int longestSpan() const;
};

#endif
