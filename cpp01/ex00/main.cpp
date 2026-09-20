#include "Zombie.hpp"

int main()
{
    randomChump("foo");
    Zombie* zPtr = newZombie("Bazghoro");
    zPtr->announce();
    delete zPtr;
    return 0;
}