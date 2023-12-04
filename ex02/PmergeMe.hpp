/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:20:47 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/04 14:25:29 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stack>
#include <limits>
#include <vector>
#include <algorithm>
#include <deque>
#include <iomanip>

class Pmerge
{
    private:
        std::vector<int> vector;
        std::deque<int> deque;
    public:
        Pmerge();
        ~Pmerge();
        Pmerge(const Pmerge& copy);
        Pmerge& operator=(const Pmerge& copy);
    
        int checknumbers(char **av);
        void printNumbers(int sw) const;
        void mergeInsertionSort();
        void mergeInsertionSortHelper(int left, int right);
        void merge(int left, int middle, int right);
        void sortvector();
        void sortdeque();
        void mergeDeque(int left, int middle, int right);
        void mergeInsertionSortDequeHelper(int left, int right);
        void mergeInsertionSortDeque();
};

void errormessage(int error_code);

#endif