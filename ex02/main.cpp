/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:21:31 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/04 14:25:45 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    Pmerge merge;
    if (ac == 1)
    {
        std::cout << "Error: Wrong amount of arguments\n";
        return 1;
    }
    int error_code = merge.checknumbers(av);
    if (error_code != 0)
    {
        errormessage(error_code);
        return 1;
    }
    merge.sortvector();
    merge.sortdeque();
    return 0;
}
