// #include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

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
    ScavTrap scav1("krawisa");
    scav1.attack("Bazghoro");
    scav1.guardGate();
    FragTrap frag1("chichawa");
    frag1.attack("krawisa");
    frag1.highFivesGuys();
    return 0;
}