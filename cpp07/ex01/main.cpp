#include "iter.hpp"

void print(const int &a)
{
  std::cout << a << std::endl;
}

void to_upper(std::string &str)
{
  for (size_t i = 0; i < str.length(); i++)
    str[i] = std::toupper(str[i]);
}

int main()
{
  std::string arr[3] = {"bazghoro", "top", "bla stop"};
  size_t len = 3;
  iter(arr, len, to_upper);
  for (size_t i = 0; i < len; i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;

  const int arr2[5] = {1, 2, 3, 4, 5};
  size_t len2 = 5;
  iter(arr2, len2, print);
}
