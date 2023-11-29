/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:17:21 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/29 14:14:51 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
    Rpn rpn;
    if (ac != 2)
    {
        std::cout << "Error: wrong amount of arguments\n";
        return 1;
    }
    int error_code = rpn.checknumbers(av[1]);
    if (error_code != 0)
    {
        errormessage(error_code);
        return 1;
    }
    error_code = rpn.processRpnExpression(av[1]);
    if (error_code != 0) errormessage(error_code);
    return 0;
}