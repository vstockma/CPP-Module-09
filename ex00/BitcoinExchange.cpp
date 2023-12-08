/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:27:46 by vstockma          #+#    #+#             */
/*   Updated: 2023/12/08 14:56:03 by vstockma         ###   ########.fr       */
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

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");

    if (first == std::string::npos || last == std::string::npos)
        return "";
    return str.substr(first, last - first + 1);
}

std::string getCurrentDate()
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int BitcoinExchange::checkdate(const std::string& date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-' || date.find('-', 5) != 7 || date.find('-', 8) != std::string::npos) {
        std::cerr << "Error: invalid date format: " << date << std::endl;
        return 1;
    }
    int year, month, day;
    char dash;

    std::istringstream dateStream(date);
    dateStream >> year >> dash >> month >> dash >> day;

    if (dateStream.fail() || !dateStream.eof()) {
        std::cerr << "Error: invalid date format: " << date << std::endl;
        return 1;
    }
    if (year < 0 || month < 1 || month > 12 || day < 1) {
        std::cerr << "Error: invalid date: " << date << std::endl;
        return 1;
    }
    std::string currentDate = getCurrentDate();
    if (date > currentDate) {
        std::cerr << "Error: Date cannot be in the future: " << date << std::endl;
        return 1;
    }
    int daysInMonth = (month == 2 && isLeapYear(year)) ? 29 : 31;

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else if (month == 2) {
        daysInMonth = isLeapYear(year) ? 29 : 28;
    }
    if (day > daysInMonth) {
        std::cerr << "Error: invalid date: " << date << std::endl;
        return 1;
    }
    return 0;
}

int BitcoinExchange::checkvalue(const std::string& value)
{
    if (value.empty()) {
        std::cerr << "Error: Value is empty" << std::endl;
        return 1;
    }
    char* endptr;
    double floatValue = strtod(value.c_str(), &endptr);

    if (*endptr != '\0') {
        std::cerr << "Error: invalid value format => " << value << std::endl;
        return 1;
    }
    if (floatValue < 0 || floatValue > 1000) {
        std::cerr << "Error: value not in range => " << value << std::endl;
        return 1;
    }
    return 0;
}

void BitcoinExchange::processInputLine(const std::string& date_str, const std::string& value_str)
{
    float input_value;
    std::istringstream(value_str) >> input_value;

    std::map<std::string, float>::iterator it = map.find(date_str);
    if (map.empty())
        std::cout << "Error: can not find date cause file is empty" << std::endl;
    else if (it != map.end())
    {
        float stored_value = it->second;
        float result_value = input_value * stored_value;

        std::cout << date_str << " => " << input_value << " = " << result_value << std::endl;
    }
    else
    {
        it = map.lower_bound(date_str);

        if (it != map.begin())
            --it;
        float result_value = it->second * input_value;
        std::cout << date_str << " => " << input_value << " = " << result_value << std::endl;
    }
}

int BitcoinExchange::output(std::string file)
{
    std::ifstream inputFile(file.c_str());

    if (!inputFile.is_open()) {
        std::cerr << "Error opening file: " << file << std::endl;
        return 1;
    }
    std::string line;

    while (std::getline(inputFile, line))
    {
        size_t pos = line.find('|');

        if (pos != std::string::npos) {
            std::string date_str = trim(line.substr(0, pos));
            std::string value_str = trim(line.substr(pos + 1));

            if (checkdate(date_str) != 0)
                continue;
            if (checkvalue(value_str) != 0)
                continue;
            processInputLine(date_str, value_str);
        } else
            std::cerr << "Error: wrong format => " << line << std::endl;
    }
    inputFile.close();
    return 0;
}

char getdelimiter(const std::string& line)
{
    for (std::string::const_iterator it = line.begin(); it != line.end(); ++it)
    {
        char ch = *it;
        if (!std::isalnum(ch))
            return ch;
    }
    return '\0';
}

int BitcoinExchange::getmap(std::istream& inputStream)
{
    std::string line;
    bool isFirstLine = true;
    char delimiter;
    while (std::getline(inputStream, line))
    {
        if (isFirstLine && std::isalpha(line[0]))
        {
            delimiter = getdelimiter(line);
            isFirstLine = false;
            continue;
        }
        else if (isFirstLine)
        {
            delimiter = getdelimiter(line);
            isFirstLine = false;
        }
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string date_str, value_str;

        if (std::getline(iss, date_str, delimiter) && std::getline(iss >> std::ws, value_str))
        {
            size_t invalidCharPos = value_str.find_first_not_of("0123456789.");
            if (invalidCharPos == std::string::npos)
            {
                float value;
                std::istringstream(value_str) >> value;
                map.insert(std::make_pair(date_str, value));
            }
        }
    }
    return 0;
}
