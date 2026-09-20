#include "Zombie.hpp"

Zombie::Zombie() {

}

void Zombie::setName(std::string sname) {
    name = sname;
}

void Zombie::announce()
{
    std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

Zombie::~Zombie()
{
    std::cout << name << " is destroyed." << std::endl;
}