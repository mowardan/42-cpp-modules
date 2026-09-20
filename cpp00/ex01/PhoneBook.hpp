#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
    Contact contacts[8];
    int next_index;
    int count;
public:
    PhoneBook();
    void core(void);
    void add_contact();
    void display_element(void);
};

static std::string truncate(std::string str);

#endif