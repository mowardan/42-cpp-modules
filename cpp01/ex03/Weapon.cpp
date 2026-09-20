#include "Weapon.hpp"

Weapon::Weapon(const std::string& initialType) { 
    type = initialType;
}

const std::string& Weapon::getType() { 
    return type;
}

void Weapon::setType(const std::string& newType) {
    type = newType;
}