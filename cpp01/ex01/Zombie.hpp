#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>

class Zombie {
    std::string name;

public:
    Zombie();
    ~Zombie();
    void announce(void);
    void setName(std::string sname);
};

Zombie* zombieHorde(int N, std::string name);

#endif