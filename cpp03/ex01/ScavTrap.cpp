#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("Default_ScavTrap")
{
    std::cout << "ScavTrap " << "Default_ScavTrap" << " constructed with default values." << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
    std::cout << "ScavTrap " << name << " constructed." << std::endl;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << name << " destructed." << std::endl;
}

void ScavTrap::attack(const std::string &target)
{
    if (energy_points > 0 && hitpoints > 0)
    {
        energy_points--;
        std::cout << "ScavTrap " << name << " attacks " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
    }
    else
    {
        std::cout << "ScavTrap " << name << " has insufficient energy or hitpoints to attack." << std::endl;
    }
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << name << " is now in Gate Keeper mode." << std::endl;
}