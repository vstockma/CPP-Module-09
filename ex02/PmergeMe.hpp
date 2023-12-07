/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:20:47 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/07 15:50:22 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
#define PMERGE_HPP

# include <iostream>
# include <cstdlib>
# include <sstream>
# include <vector>
# include <deque>
# include <ctime>
# include <iomanip>
# include <algorithm>
#include <limits>

struct Pmerge
{
    std::vector<int> vector;
    std::vector<std::pair<int, int> >   pairvector;
    std::vector<int> finalvector;

    std::deque<int> deque;
    std::deque<std::pair<int, int> >   pairdeque;
    std::deque<int> finaldeque;

    int     checknumbers(char **av);
    void    printNumbers(int sw, char **av) const;
};

void    makepairvector(Pmerge* merge);
void    findBiggerNumVector(Pmerge* merge);
void    SortingpairVector(std::vector<std::pair<int, int> >& pair);
void    mergeVector(std::vector<std::pair<int, int> >& left, std::vector<std::pair<int, int> >& right, std::vector<std::pair<int, int> >& middle);
void    startFinalVector(Pmerge* merge);
void    finishFinalVectorInsertion(Pmerge* merge);
std::vector<int>::iterator binaryVector(std::vector<int>& finalvector, int number);

void    makepairdeque(Pmerge* merge);
void    findBiggerNumDeque(Pmerge* merge);
void    SortingpairDeque(std::deque<std::pair<int, int> >& pair);
void    mergeDeque(std::deque<std::pair<int, int> >& left, std::deque<std::pair<int, int> >& right, std::deque<std::pair<int, int> >& middle);
void    startFinalDeque(Pmerge* merge);
void    finishFinalDequeInsertion(Pmerge* merge);
std::deque<int>::iterator binaryDeque(std::deque<int>& finaldeque, int number);

void    errormessage(int error_code);
int issorted(char **av, int ac);

#endif