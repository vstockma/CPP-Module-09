/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:27:46 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/22 16:58:06 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& copy)
{
    *this = copy;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& copy)
{
    map = copy.map;
    return *this;
}

void trim(std::string& str)
{
    // Remove leading spaces
    std::string::size_type first = str.find_first_not_of(" \t\n\r");
    if (first != std::string::npos)
        str = str.substr(first);

    // Remove trailing spaces
    std::string::size_type last = str.find_last_not_of(" \t\n\r");
    if (last != std::string::npos)
        str = str.substr(0, last + 1);
}

int BitcoinExchange::checkvalue(float value)
{
    (void)value;
    return 0;
}

int BitcoinExchange::checkdate(const std::string& date)
{
    if (date == "invalidvalue")
    {
        std::cout << "Error: invalid format for value\n";
        return 1;
    }
    std::istringstream dateStream(date);
    int year, month, day;

    char delimiter1, delimiter2;
    dateStream >> year >> delimiter1 >> month >> delimiter2 >> day;
    if (dateStream.fail() || delimiter1 != '-' || delimiter2 != '-' ||
        month < 1 || month > 12 || day < 1 ||
        (month == 2 && day > 28 + (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))))
    {
        std::cout << "Error: \"" << date << "\" is not a valid date\n";
        return 1;
    }
    // Get the current date
    std::time_t t = std::time(0);
    std::tm* now = std::localtime(&t);
    int currentYear = now->tm_year + 1900;
    int currentMonth = now->tm_mon + 1;
    int currentDay = now->tm_mday;
    // Check if the date exceeds the current date
    if (year > currentYear ||
        (year == currentYear && month > currentMonth) ||
        (year == currentYear && month == currentMonth && day > currentDay))
    {
        std::cout << "Error: \"" << date << "\" exceeds the current date\n";
        return 2;
    }
    return 0;  // Valid date format
}


void BitcoinExchange::multiplyValuesFromFile(const std::string& filename)
{
    std::ifstream newFile(filename.c_str());
    if (!newFile.is_open())
    {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return;
    }
    newFile.close();
    for (std::multimap<std::string, float>::iterator it = map.begin(); it != map.end(); ++it)
    {
        if (checkdate(it->first) == 0 && checkvalue(it->second) == 0)
            ;
        else
        {
            std::ifstream newFile(filename.c_str());
            if (!newFile.is_open())
            {
                std::cerr << "Error opening file for reading: " << filename << std::endl;
                return;
            }
            std::string line;
            while (std::getline(newFile, line))
            {
                std::istringstream lineStream(line);
                std::string date;
                float value;

                if (std::getline(lineStream, date, ',') && lineStream >> value)
                {
                    trim(date);
                    // If the date is found in the multimap, multiply the values
                    if (date == it->first)
                    {
                        std::cout << it->second * value << std::endl;
                    }
                }
            }
            newFile.close();
        }  
    }
}

void BitcoinExchange::getmap(std::istream& inputStream)
{
    std::string line;
    while (std::getline(inputStream, line))
    {
        std::istringstream lineStream(line);
        std::string date;
        float value;

        // Assuming that the format of each line is "date|value"
        if (std::getline(lineStream, date, '|') && lineStream >> value)
        {
            trim(date);
            std::string valueStr;
            // Check if there is more content in the line after the value
            if (lineStream >> valueStr)
            {
                char* endptr;
                value = strtof(valueStr.c_str(), &endptr);

                // Check if the entire value was successfully converted
                if (endptr == valueStr.c_str() || *endptr != '\0')
                {
                    // Insert an "invalidvalue" entry into the multimap with a default float value
                    map.insert(std::make_pair("invalidvalue", 0.0));
                    continue; // Skip the rest of the loop for this line
                }
            }
            map.insert(std::make_pair(date, value));
        }
        else
            map.insert(std::make_pair("invalid" + date, 0.0));
    }
}