#ifndef ITER_HPP
# define ITER_HPP

#include <iostream>

template <typename T , typename U >
void iter(T *arr, size_t len, U function)
{
  for (size_t i = 0; i < len; i++)
    function(arr[i]);
}


template <typename T , typename U >
void iter(const T* arr, size_t len, U function)
{
  for (size_t i = 0; i < len; i++)
    function(arr[i]);
} 

#endif
