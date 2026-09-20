/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 06:35:46 by mowardan          #+#    #+#             */
/*   Updated: 2025/11/24 06:35:50 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
    next_index = 0;
    count = 0;
}

void PhoneBook::core()
{
    std::string command;
    Contact contact;

    std::cout << "\033[33mADD, SEARCH or EXIT :\033[0m";
    if(!getline(std::cin, command))
        return ;
    if(command == "ADD")
        PhoneBook::add_contact();
    if(command == "SEARCH")
        PhoneBook::display_element();
    if(command == "EXIT")
        return ;
    core();
}

static std::string truncate(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

void PhoneBook::display_element()
{
    if(count == 0)
    {
        std::cout << "\033[31mPhoneBook is empty. Please add contacts first.\033[0m" << std::endl;
        return;
    }
    std::cout << std::setw(10) << "    \033[36mIndex\033[0m " << " | "
              << std::setw(10) << "\033[36mFirst Name\033[0m " << "| "
              << std::setw(10) << "\033[36mLast Name\033[0m " << " | "
              << std::setw(10) << "\033[36mNickname\033[0m" << std::endl;
    for(int i = 0; i < 8; i++)
    {
        Contact &c = contacts[i];
        std::cout << std::setw(10) << i << " | "
              << std::setw(10) << truncate(c.getName()) << " | "
              << std::setw(10) <<  truncate(c.getLastName()) << " | "
              << std::setw(10) << truncate(c.getNickName()) << std::endl;
    }
    std::cout << "\033[34mEnter index to view details: \033[0m";
    std::string index;
    if(!getline(std::cin, index))
        return;
    if (index.size() != 1)
    {
        std::cout << "\033[31mTHE INDEX RANGE SHOULD BE (0-7)\033[0m" << std::endl;
        return ;
    }
    int idx = index[0] - 48;
    if(idx < 0 || idx >= count)
    {
        std::cout << "\033[31mInvalid index.\033[0m" << std::endl;
        return;
    }
    contacts[idx].get();
}


void PhoneBook::add_contact()
{
    Contact c;

    if(!c.set_element())
        return;
    contacts[next_index] = c;
    next_index = (next_index + 1) % 8;
    if (count < 8)
        count++;
}
