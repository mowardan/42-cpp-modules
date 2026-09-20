#ifndef CONTACT_HPP 
#define CONTACT_HPP

#include <iostream>
#include <iomanip>

class Contact
{
    std::string name;
    std::string last_name;
    std::string nick_name;
    std::string phone_number;
    std::string darkest_secret;
public:
    bool set_element();
    void get();
    bool checktheelemts();
    const std::string& getName();
    const std::string& getLastName();
    const std::string& getNickName();
};

#endif