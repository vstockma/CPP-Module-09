/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:12:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/23 15:29:22 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    (void)av;
    BitcoinExchange btc;
    if (ac != 2)
    {
        std::cout << "Error: wrong number of arguments\n";
        return 0;
    }
    std::ifstream inputFile("data.csv");
    if (!inputFile.is_open())
        std::cerr << "Error opening file for reading.\n";
    if (btc.getmap(inputFile) == 1)
    {
        inputFile.close();
        return 1;
    }
    inputFile.close();
    btc.output(av[1]);
    // for (std::map<std::string, float>::const_iterator it = btc.map.begin(); it != btc.map.end(); ++it) {
    //     std::cout << it->first << " | " << it->second << std::endl;
    // }
    // std::map<std::string, float>::const_iterator it = btc.map.begin();
    // for (int i = 0; i < 10; ++i)
    // {
    //     std::cout << it->first << " | " << it->second << std::endl;
    //     it++;
    // }
    return 0;
}