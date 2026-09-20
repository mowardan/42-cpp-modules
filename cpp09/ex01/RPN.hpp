#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

class RPN {
  private:
    std::stack<int> stack;
  public:
    RPN();
    RPN(const RPN& other);
    RPN& operator=(const RPN& other);
    ~RPN();
    void evaluate(const std::string& str);
};

#endif
