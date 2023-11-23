/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:27:46 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/23 15:57:19 by vstockma         ###   ########.fr       */
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

int BitcoinExchange::checkvalue(const std::string& value)
{
    (void)value;
    return 0;
}

std::string getCurrentDate()
{
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", timeinfo);
    return std::string(buffer);
}

int BitcoinExchange::checkdate(const std::string& date)
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-'
        || date.find('-', 5) != 7 || date.find('-', 8) != std::string::npos)
    {
        std::cerr << "Error: Invalid date format: " << date << std::endl;
        return 1;
    }

    struct tm timeinfo;
    if (strptime(date.c_str(), "%Y-%m-%d", &timeinfo) == NULL || date > getCurrentDate())
    {
        std::cerr << "Error: Invalid date: " << date << std::endl;
        return 1;
    }
    return 0;
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
            std::cout << date_str << " | " << value_str << std::endl;
        } else
            std::cerr << "Error: wrong format => " << line << std::endl;
    }
    inputFile.close();
    return 0;
}

int BitcoinExchange::getmap(std::istream& inputStream)
{
    std::string line;
    bool isFirstLine = true;

    while (std::getline(inputStream, line)) {
        if (isFirstLine && std::isalpha(line[0])) {
            isFirstLine = false;
            continue;
        }
        if (line.empty())
            continue;
        std::istringstream iss(line);
        std::string date_str, value_str;

        if (std::getline(iss, date_str, ',') && std::getline(iss >> std::ws, value_str)) {
            if (date_str.size() != 10 || date_str[4] != '-' || date_str[7] != '-') {
                std::cerr << "Invalid date format at line: " << line << std::endl;
                return 1;
            }

            size_t invalidCharPos = value_str.find_first_not_of("0123456789.");
            if (invalidCharPos == std::string::npos) {
                float value;
                std::istringstream(value_str) >> value;
                map.insert(std::make_pair(date_str, value));
            } else {
                std::cerr << "Invalid value at line: " << line << std::endl;
                return 1;
            }
        } else {
            std::cerr << "Error at line: " << line << std::endl;
            return 1;
        }
    }
    return 0;
}
