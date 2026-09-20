/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 06:36:08 by mowardan          #+#    #+#             */
/*   Updated: 2025/08/19 06:36:43 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

bool Contact::set_element()
{
    std::cout << "enter name:";
    if(!getline(std::cin, name))
        return false;
    std::cout << "enter last name:";
    if(!getline(std::cin, last_name))
        return false;
    std::cout << "enter nick name:";
    if(!getline(std::cin, nick_name))
        return false;
    std::cout << "enter phone number:";
    if(!getline(std::cin, phone_number))
        return false;
    std::cout << "enter darkest secret:";
    if(!getline(std::cin, darkest_secret))
        return false;
    if(!checktheelemts())
        return false;
    return true;
}

bool Contact::checktheelemts()
{
    if (name.empty() || last_name.empty() || nick_name.empty() ||
        phone_number.empty() || darkest_secret.empty())
    {
        std::cout << "\033[31mthe elements must not be empty\033[0m" << std::endl;
        return false;
    }
    return true;
}

void Contact::get()
{
    std::cout << name  << std::endl;
    std::cout << last_name << std::endl;
    std::cout << nick_name << std::endl;
    std::cout << phone_number << std::endl;
    std::cout << darkest_secret << std::endl;
}

const std::string& Contact::getName()
{
    return name;
}

const std::string& Contact::getLastName()
{
    return last_name;
}

const  std::string& Contact::getNickName()
{
    return nick_name;
}