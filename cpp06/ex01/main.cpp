#include <iostream>
#include "Serializer.hpp"

int main()
{
  Data myData;
  myData.id = 42;
  myData.name = "Test Data";

  std::cout << "Original Data address: " << &myData << std::endl;
  std::cout << "Original Data.id: " << myData.id << std::endl;
  std::cout << "Original Data.name: " << myData.name << std::endl;
  std::cout << "-----------------------------" << std::endl;

  uintptr_t raw = Serializer::serialize(&myData);
  std::cout << "Serialized (uintptr_t): " << raw << std::endl;

  std::cout << "-----------------------------" << std::endl;
  Data *deserializedData = Serializer::deserialize(raw);
  std::cout << "Deserialized Data address: " << deserializedData << std::endl;
  std::cout << "Deserialized Data.id: " << deserializedData->id << std::endl;
  std::cout << "Deserialized Data.name: " << deserializedData->name << std::endl;

  std::cout << "-----------------------------" << std::endl;
  if (&myData == deserializedData)
  {
    std::cout << "SUCCESS: The pointers match!" << std::endl;
  }
  else
  {
    std::cout << "ERROR: The pointers do not match!" << std::endl;
  }

  return 0;
}