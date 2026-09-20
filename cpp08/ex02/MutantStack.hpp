#ifndef MUTANTSTACK_HPP
#define MUTANTSTACK_HPP

#include <stack>
#include <iterator>
#include <iostream>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
  MutantStack() {}
  MutantStack(const MutantStack &other) : std::stack<T>(other) {}
  ~MutantStack() {}
  MutantStack &operator=(const MutantStack &other)
  {
    if (this != &other)
      std::stack<T>::operator=(other);
    return *this;
  }

  typedef typename std::stack<T>::container_type::iterator iterator;
  typedef typename std::stack<T>::container_type::const_iterator const_iterator;

  iterator begin() { return std::stack<T>::c.begin(); }
  iterator end() { return std::stack<T>::c.end(); }
  const_iterator begin() const { return std::stack<T>::c.begin(); }
  const_iterator end() const { return std::stack<T>::c.end(); }
};

#endif