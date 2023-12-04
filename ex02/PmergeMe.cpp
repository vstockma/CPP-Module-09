/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:21:18 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/04 14:25:01 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

Pmerge::Pmerge()
{
}

Pmerge::~Pmerge()
{
}

Pmerge::Pmerge(const Pmerge& copy)
{
    *this = copy;
}

Pmerge& Pmerge::operator=(const Pmerge& copy)
{
    if (this != &copy)
    {
        vector = copy.vector;
        deque = copy.deque;
    }
    return *this;
}

void errormessage(int error_code)
{
	if (error_code == 1) std::cout << "Error: empty file\n";
	else if (error_code == 2) std::cout << "Error: no space before number\n";
	else if (error_code == 3) std::cout << "Error: number is not a positive int\n";
	else if (error_code == 4) std::cout << "Error: wrong character\n";
	else if (error_code == 5) std::cout << "Error: duplicate number\n";
}

void Pmerge::printNumbers(int sw) const
{
    if (sw == 1)
        std::cout << "Before:";
    else if (sw == 2)
        std::cout << "After:";
    for (std::vector<int>::const_iterator it = vector.begin(); it != vector.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;
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
                if (j > 0 && !std::isspace(input[j - 1])) return 2;
                std::size_t start = j;
                std::size_t end = input.find_first_not_of("0123456789", start);
                std::string numStr = input.substr(start, end - start);
                j = end - 1;
                long number = std::strtol(numStr.c_str(), NULL, 10);

                if (number > 2147483647 || number < std::numeric_limits<int>::min())
                    return 3;
                if (std::find(vector.begin(), vector.end(), static_cast<int>(number)) != vector.end())
                    return 5;
                else
                    vector.push_back(static_cast<int>(number));
                deque.push_back(static_cast<int>(number));
            }
            else if (std::isspace(input[j])) continue;
            else return 4;
        }
    }
    return 0;
}

void Pmerge::mergeInsertionSort()
{
    mergeInsertionSortHelper(0, vector.size() - 1);
}

void Pmerge::mergeInsertionSortHelper(int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeInsertionSortHelper(left, middle);
        mergeInsertionSortHelper(middle + 1, right);

        // Merge the sorted halves
        merge(left, middle, right);
    }
}

void Pmerge::merge(int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary vectors
    std::vector<int> leftVector(n1);
    std::vector<int> rightVector(n2);

    // Copy data to temporary vectors leftVector[] and rightVector[]
    for (int i = 0; i < n1; i++)
        leftVector[i] = vector[left + i];
    for (int j = 0; j < n2; j++)
        rightVector[j] = vector[middle + 1 + j];

    // Merge the temporary vectors back into numbers_vector[left...right]
    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (leftVector[i] <= rightVector[j])
        {
            vector[k] = leftVector[i];
            i++;
        }
        else
        {
            vector[k] = rightVector[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftVector[], if there are any
    while (i < n1)
    {
        vector[k] = leftVector[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightVector[], if there are any
    while (j < n2)
    {
        vector[k] = rightVector[j];
        j++;
        k++;
    }
}

void Pmerge::sortvector()
{
    printNumbers(1);
    clock_t start_time = clock();

    this->mergeInsertionSort();

    clock_t end_time = clock();
    double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    printNumbers(2);
    std::ostringstream timeStringStream;
    timeStringStream << "Time to process a range of " << vector.size() << " elements with std::vector: " << std::fixed << std::setprecision(6) << duration << " seconds";
    std::cout << timeStringStream.str() << std::endl;
}

void Pmerge::mergeInsertionSortDeque()
{
    mergeInsertionSortDequeHelper(0, deque.size() - 1);
}

void Pmerge::mergeInsertionSortDequeHelper(int left, int right)
{
    if (left < right)
    {
        int middle = left + (right - left) / 2;

        // Recursively sort the two halves
        mergeInsertionSortDequeHelper(left, middle);
        mergeInsertionSortDequeHelper(middle + 1, right);

        // Merge the sorted halves
        mergeDeque(left, middle, right);
    }
}

void Pmerge::mergeDeque(int left, int middle, int right)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary deques
    std::deque<int> leftDeque(n1);
    std::deque<int> rightDeque(n2);

    // Copy data to temporary deques leftDeque[] and rightDeque[]
    for (int i = 0; i < n1; i++)
        leftDeque[i] = deque[left + i];
    for (int j = 0; j < n2; j++)
        rightDeque[j] = deque[middle + 1 + j];

    // Merge the temporary deques back into deque[left...right]
    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (leftDeque[i] <= rightDeque[j])
        {
            deque[k] = leftDeque[i];
            i++;
        }
        else
        {
            deque[k] = rightDeque[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftDeque[], if there are any
    while (i < n1)
    {
        deque[k] = leftDeque[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightDeque[], if there are any
    while (j < n2)
    {
        deque[k] = rightDeque[j];
        j++;
        k++;
    }
}

void Pmerge::sortdeque()
{
    clock_t start_time = clock();

    this->mergeInsertionSortDeque();

    clock_t end_time = clock();
    double duration = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    std::ostringstream timeStringStream;
    timeStringStream << "Time to process a range of " << deque.size() << " elements with std::deque: " << std::fixed << std::setprecision(6) << duration << " seconds";
    std::cout << timeStringStream.str() << std::endl;
}

