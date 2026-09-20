#ifndef   ARRAY_HPP
# define  ARRAY_HPP

#include <iostream>

template <typename T>
class Array
{
private:
  T *array;
  size_t array_size;
public:
  Array() : array(nullptr), array_size(0) {}
  Array(unsigned int n) : array(new T[n]()), array_size(n) {}
  Array(const Array &other) : array(new T[other.array_size]()), array_size(other.array_size)
  {
    for (size_t i = 0; i < array_size; i++)
      array[i] = other.array[i];
  }
  ~Array() {
    delete[] array;
  }
  Array &operator=(const Array &other)
  {
    if (this != &other)
    {
      delete[] array;
      array_size = other.array_size;
      array = new T[array_size]();
      for (size_t i = 0; i < array_size; i++)
        array[i] = other.array[i];
    }
    return *this;
  }
  T &operator[](size_t index)
  {
    if (index >= array_size)
      throw std::out_of_range("Index out of range");
    return array[index];
  }
  const T &operator[](size_t index) const
  { 
    if (index >= array_size)
      throw std::out_of_range("Index out of range");
    return array[index];
  }
  size_t size() const { return  array_size; }
}; 

#endif