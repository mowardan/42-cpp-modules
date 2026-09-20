#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon
{
    std::string type;

public:
    Weapon(const std::string &initialType);
    const std::string &getType();
    void setType(const std::string &newType);
};

#endif