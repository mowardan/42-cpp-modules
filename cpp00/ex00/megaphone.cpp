/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mowardan <mowardan@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 06:25:21 by mowardan          #+#    #+#             */
/*   Updated: 2025/08/20 10:22:32 by mowardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>


int main(int ac, char **av)
{
	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		std::string txt;
		int i = 1;
		while(av[i])
		{
			int j = 0;
			while(av[i][j])
			{
				if(av[i][j] >= 'a' && av[i][j] <= 'z')
					av[i][j] -= 32;
				else
					j++;
			}
			std::cout << av[i];	
			i++;
		}
		std::cout << txt;
	}
	std::cout << std::endl;
	return (0);
}