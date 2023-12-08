/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:12:13 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/08 12:56:32 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
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
    return 0;
}