#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongCat.hpp"

int main()
{

const Animal* meta = new Animal();
const Animal* j = new Dog();
const Animal* i = new Cat();
std::cout << j->getType() << " " << std::endl;
std::cout << i->getType() << " " << std::endl;
i->makeSound(); //will output the cat sound!
j->makeSound();
meta->makeSound();

std::cout << "---------------------" << std::endl;

// const WrongAnimal* wrongMeta = new WrongAnimal();
const WrongAnimal* wrongCat = new WrongCat();
std::cout << wrongCat->getType()<< std::endl;
wrongCat->makeSound();
// wrongMeta->makeSound();
std::cout << "---------------------" << std::endl;

delete meta;
delete j;
delete i;
// delete wrongMeta;
delete wrongCat;

return 0;
}