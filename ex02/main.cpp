/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:21:31 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/07 15:51:56 by vstockma         ###   ########.fr       */
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
    if (issorted(av, ac) == 1) return 1;
    merge.printNumbers(1, av);

    clock_t start_time = clock();
    for (int i = 1; i < ac; i++)
        merge.vector.push_back(atoi(av[i]));
    makepairvector(&merge);
    findBiggerNumVector(&merge);
    SortingpairVector(merge.pairvector);
    startFinalVector(&merge);
    finishFinalVectorInsertion(&merge);
    clock_t end_time = clock();
    double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    
    merge.printNumbers(2, av);
    std::cout << "Time to process a range of " << ac - 1 << " elements with std::vector:  "; 
    
    std::cout << std::fixed << duration << std::setprecision(6) << " us"<< std::endl;
    
    start_time = clock();
    for (int i = 1; i < ac; i++)
        merge.deque.push_back(atoi(av[i]));
    makepairdeque(&merge);
    findBiggerNumDeque(&merge);
    SortingpairDeque(merge.pairdeque);
    startFinalDeque(&merge);
    finishFinalDequeInsertion(&merge);
    end_time = clock();
    duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
    
    std::cout << "Time to process a range of " << ac - 1 << " elements with std::deque:  "; 
    std::cout << std::fixed << duration << std::setprecision(6) << " us"<< std::endl;
    return 0;
}
