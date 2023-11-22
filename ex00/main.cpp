/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:12:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/22 14:07:22 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    BitcoinExchange btc;
    if (ac != 2)
    {
        std::cout << "Error: could not open file.\n";
        return 0;
    }

    std::ifstream inputFile(av[1]);
    if (!inputFile.is_open())
        std::cerr << "Error opening file for reading.\n";
    btc.getmap(inputFile);
    inputFile.close();
    btc.multiplyValuesFromFile("data.csv");
    for (std::map<std::string, float>::const_iterator it = btc.map.begin(); it != btc.map.end(); ++it) {
        std::cout << it->first << " | " << it->second << std::endl;
    }
    return 0;
}