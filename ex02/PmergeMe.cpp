/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:21:18 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/07 16:41:08 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void errormessage(int error_code)
{
	if (error_code == 1) std::cout << "Error: empty file\n";
	else if (error_code == 2) std::cout << "Error: number is not a positive int\n";
	else if (error_code == 3) std::cout << "Error: duplicate number\n";
	else if (error_code == 4) std::cout << "Error: wrong character\n";
}

int issorted(char **av, int ac)
{
    for (int i = 1; i < ac - 1; i++)
    {
        int current = atoi(av[i]);
        int next = atoi(av[i + 1]);

        if (current > next) return 0;
    }
    std::cout << "Already sorted\n";
    return 1;
}

void Pmerge::printNumbers(int sw, char **av) const
{
    if (sw == 1)
    {
        std::cout << "Before: ";
        for (int i = 1; av[i] != NULL; i++)
            std::cout << av[i] << " ";
    }
    else if (sw == 2)
    {
        std::cout << "After:";
        for (std::vector<int>::const_iterator it = finalvector.begin(); it != finalvector.end(); ++it)
            std::cout << " " << *it;

    }
    std::cout << std::endl;
}

int dupnumber(char **av, long num, int i)
{
    for (int j = 1; j < i; ++j)
    {
        std::string input(av[j]);
        std::size_t end = input.find_first_not_of("0123456789", 0);
        std::string numStr = input.substr(0, end);
        long number = std::strtol(numStr.c_str(), NULL, 10);
        if (number == num) return 1;      
    }
    return 0;
}

int Pmerge::checknumbers(char **av)
{
	for (int i = 1; av[i] != NULL; ++i)
		{
			std::string input(av[i]);
			if (input.empty()) return 1;
			for (std::size_t j = 0; j < input.size(); ++j)
			{
				if (std::isdigit(input[j]))
				{
					std::size_t start = j;
					std::size_t end = input.find_first_not_of("0123456789", start);
					std::string numStr = input.substr(start, end - start);
					j = end - 1;
					long number = std::strtol(numStr.c_str(), NULL, 10);
					if (number > 2147483647 || number < std::numeric_limits<int>::min()) return 2;
					if (dupnumber(av, number, i) == 1) return 3;
				}
				else return 4;
			}
		}
	return 0;
}

void    makepairvector(Pmerge* merge)
{
    for (size_t i = 0; i < merge->vector.size() - 1; i += 2)
        merge->pairvector.push_back(std::pair<int, int>(merge->vector[i], merge->vector[i + 1]));
    if (merge->vector.size() % 2 != 0)
        merge->pairvector.push_back(std::make_pair(merge->vector[merge->vector.size() - 1], -1));
}

void    findBiggerNumVector(Pmerge* merge)
{
    for (std::vector<std::pair<int, int> >::iterator it = merge->pairvector.begin(); it != merge->pairvector.end(); it++)
        if (it->second > it->first) std::swap(it->first, it->second);
}

void    SortingpairVector(std::vector<std::pair<int, int> >& pair)
{
    if (pair.size() < 2) return ;
    unsigned int middle = pair.size() / 2;
    std::vector<std::pair<int, int> >    left;
    std::vector<std::pair<int, int> >    right;
    for (size_t i = 0; i < pair.size(); i++)
        (i < middle) ? left.push_back(pair[i]) : right.push_back(pair[i]);
    SortingpairVector(left);
    SortingpairVector(right);
    mergeVector(left, right, pair);
}

void    mergeVector(std::vector<std::pair<int, int> >& left, std::vector<std::pair<int, int> >& right, std::vector<std::pair<int, int> >& middle)
{
    size_t i = 0, j = 0, k = 0;
    for (; j < left.size() && k < right.size(); ++i)
    {
        if (left[j].first < right[k].first)
            middle[i] = left[j++];
        else
            middle[i] = right[k++];
    }
    for (; j < left.size(); ++j, ++i)
        middle[i] = left[j];
    for (; k < right.size(); ++k, ++i)
        middle[i] = right[k];
}

void    startFinalVector(Pmerge* merge)
{
    std::vector<std::pair<int, int> >::iterator it = merge->pairvector.begin();
    for (; it != merge->pairvector.end(); it++)
        merge->finalvector.push_back(it->first);
    it = merge->pairvector.begin();
    if (it->second >= 0)
        merge->finalvector.insert(merge->finalvector.begin(), it->second);
}

void    finishFinalVectorInsertion(Pmerge* merge)
{
    for (std::vector<std::pair<int, int> >::iterator it = merge->pairvector.begin() + 1; it != merge->pairvector.end(); it++)
        if (it->second >= 0) merge->finalvector.insert(binaryVector(merge->finalvector, it->second), it->second);
}

std::vector<int>::iterator binaryVector(std::vector<int>& finalvector, int number)
{
    std::vector<int>::iterator start = finalvector.begin();
    std::vector<int>::iterator end = finalvector.end();
    std::vector<int>::iterator middle = start + (end - start) / 2;

    while (start < end)
    {
        middle = start + (end - start) / 2;
        if (number > *middle)
            start = middle + 1;
        else
            end = middle;
    }
    return start;
}

void    makepairdeque(Pmerge* merge)
{
    for (size_t i = 0; i < merge->deque.size() - 1; i += 2)
        merge->pairdeque.push_back(std::pair<int, int>(merge->deque[i], merge->deque[i + 1]));
    if (merge->deque.size() % 2 != 0)
        merge->pairdeque.push_back(std::make_pair(merge->deque[merge->deque.size() - 1], -1));
}

void    findBiggerNumDeque(Pmerge* merge)
{
    for (std::deque<std::pair<int, int> >::iterator it = merge->pairdeque.begin(); it != merge->pairdeque.end(); it++)
        if (it->second > it->first) std::swap(it->first, it->second);
}

void    SortingpairDeque(std::deque<std::pair<int, int> >& pair)
{
    if (pair.size() < 2) return ;
    unsigned int middle = pair.size() / 2;
    std::deque<std::pair<int, int> >    left;
    std::deque<std::pair<int, int> >    right;
    for (size_t i = 0; i < pair.size(); i++)
        (i < middle) ? left.push_back(pair[i]) : right.push_back(pair[i]);
    SortingpairDeque(left);
    SortingpairDeque(right);
    mergeDeque(left, right, pair);
}

void    mergeDeque(std::deque<std::pair<int, int> >& left, std::deque<std::pair<int, int> >& right, std::deque<std::pair<int, int> >& middle)
{
    size_t i = 0, j = 0, k = 0;
    for (; j < left.size() && k < right.size(); ++i)
    {
        if (left[j].first < right[k].first)
            middle[i] = left[j++];
        else
            middle[i] = right[k++];
    }
    for (; j < left.size(); ++j, ++i)
        middle[i] = left[j];
    for (; k < right.size(); ++k, ++i)
        middle[i] = right[k];
}

void    startFinalDeque(Pmerge* merge)
{
    std::deque<std::pair<int, int> >::iterator it = merge->pairdeque.begin();
    for (; it != merge->pairdeque.end(); it++)
        merge->finaldeque.push_back(it->first);
    it = merge->pairdeque.begin();
    if (it->second >= 0)
        merge->finaldeque.insert(merge->finaldeque.begin(), it->second);
}

void    finishFinalDequeInsertion(Pmerge* merge)
{
    for (std::deque<std::pair<int, int> >::iterator it = merge->pairdeque.begin() + 1; it != merge->pairdeque.end(); it++)
        if (it->second >= 0) merge->finaldeque.insert(binaryDeque(merge->finaldeque, it->second), it->second);
}

std::deque<int>::iterator binaryDeque(std::deque<int>& finaldeque, int number)
{
    std::deque<int>::iterator start = finaldeque.begin();
    std::deque<int>::iterator end = finaldeque.end();
    std::deque<int>::iterator middle = start + (end - start) / 2;

    while (start < end)
    {
        middle = start + (end - start) / 2;
        if (number > *middle)
            start = middle + 1;
        else
            end = middle;
    }
    return start;
}
