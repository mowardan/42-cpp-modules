#include "ClapTrap.hpp"

int main()
{
    ClapTrap clap1("Bazghoro");
    ClapTrap clap2("safwan");

    clap1.attack("safwan");
    clap2.takeDamage(5);
    clap2.beRepaired(3);
    clap2.attack("Bazghoro");
    clap1.takeDamage(7);
    clap1.beRepaired(4);

    return 0;
}