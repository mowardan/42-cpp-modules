#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : name("Default"), hitpoints(10), energy_points(10), attack_damage(0)
{
    std::cout << "ClapTrap " << name << " constructed with default values." << std::endl;
}

ClapTrap::ClapTrap(std::string name) : name(name), hitpoints(10), energy_points(10), attack_damage(0)
{
    std::cout << "ClapTrap " << name << " constructed." << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &other)
{
    *this = other;
    std::cout << "ClapTrap " << name << " copy constructed." << std::endl;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &other)
{
    if (this != &other)
    {
        name = other.name;
        hitpoints = other.hitpoints;
        energy_points = other.energy_points;
        attack_damage = other.attack_damage;
    }
    return *this;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << name << " destructed." << std::endl;
}

void ClapTrap::attack(const std::string &target)
{
    if (energy_points > 0 && hitpoints > 0)
    {
        energy_points--;
        std::cout << "ClapTrap " << name << " attacks " << target << ", causing " << attack_damage << " points of damage!" << std::endl;
    }
    else
    {
        std::cout << "ClapTrap " << name << " has insufficient energy or hitpoints to attack." << std::endl;
    }
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (hitpoints > 0)
    {
        hitpoints -= amount;
        std::cout << "ClapTrap " << name << " takes " << amount << " points of damage!" << std::endl;
        if (hitpoints <= 0)
        {
            std::cout << "ClapTrap " << name << " has been destroyed!" << std::endl;
        }
    }
    else
    {
        std::cout << "ClapTrap " << name << " is already destroyed." << std::endl;
    }
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (energy_points > 0 && hitpoints > 0)
    {
        energy_points--;
        hitpoints += amount;
        std::cout << "ClapTrap " << name << " repairs itself for " << amount << " points!" << std::endl;
    }
    else
    {
        std::cout << "ClapTrap " << name << " has insufficient energy or is destroyed and cannot repair itself." << std::endl;
    }
}
