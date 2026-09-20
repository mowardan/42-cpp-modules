#include  "Array.hpp"

int main()
{
  Array<int> arr(5);
  for (size_t i = 0; i < arr.size(); i++)
    arr[i] = i + 1;
  for (size_t i = 0; i < arr.size(); i++)
    std::cout << arr[i] << " ";
  std::cout << std::endl;

  Array<std::string> strArr(3);
  strArr[0] = "Hello";
  strArr[1] = "World";
  strArr[2] = "!";
  for (size_t i = 0; i < strArr.size(); i++)
    std::cout << strArr[i] << " ";
  std::cout << std::endl;

  try {
    std::cout << arr[10] << std::endl; // This should throw an exception
  }
  catch (const std::out_of_range &e) {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}