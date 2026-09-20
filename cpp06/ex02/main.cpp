#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void)
{
  int r = std::rand() % 3;
  if (r == 0)
    return new A();
  else if (r == 1)
    return new B();
  else
    return new C();
}

void identify(Base *p)
{
  if (dynamic_cast<A *>(p))
    std::cout << "A" << std::endl;
  else if (dynamic_cast<B *>(p))
    std::cout << "B" << std::endl;
  else if (dynamic_cast<C *>(p))
    std::cout << "C" << std::endl;
  else
    std::cout << "Unknown type" << std::endl;
}

void identify(Base &p)
{
  try
  {
    (void)dynamic_cast<A &>(p);
    std::cout << "A" << std::endl;
    return;
  }
  catch (...)
  {
  }

  try
  {
    (void)dynamic_cast<B &>(p);
    std::cout << "B" << std::endl;
    return;
  }
  catch (...)
  {
  }

  try
  {
    (void)dynamic_cast<C &>(p);
    std::cout << "C" << std::endl;
    return;
  }
  catch (...)
  {
  }

  std::cout << "Unknown type" << std::endl;
}

int main()
{
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  std::cout << "Generating 5 random objects..." << std::endl;
  for (int i = 0; i < 5; ++i)
  {
    Base *obj = generate();

    std::cout << "Test " << i + 1 << ":" << std::endl;
    std::cout << "  identify(Base* p): ";
    identify(obj);

    std::cout << "  identify(Base& p): ";
    identify(*obj);

    std::cout << "---------------------------" << std::endl;
    delete obj;
  }

  return 0;
}