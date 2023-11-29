/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:16:36 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/29 14:14:11 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

Rpn::Rpn()
{
	num_count = 0;
    op_count = 0;
}

Rpn::~Rpn()
{
}

Rpn::Rpn(const Rpn& copy)
{
    *this = copy;
}

Rpn& Rpn::operator=(const Rpn& copy)
{
    num_count = copy.num_count;
    op_count = copy.op_count;
	myStack = copy.myStack;
    return *this;
}

void errormessage(int error_code)
{
	if (error_code == 1) std::cout << "Error: empty file\n";
	else if (error_code == 2) std::cout << "Error: wrong character\n";
	else if (error_code == 3) std::cout << "Error: no space before number\n";
	else if (error_code == 4) std::cout << "Error: number is not in range 0-9\n";
	else if (error_code == 5) std::cout << "Error: no space before operator\n";
	else if (error_code == 6) std::cout << "Error: not the right amount of numbers and operators\n";
	else if (error_code == 7) std::cout << "Error: Not enough numbers in stack\n";
	else if (error_code == 8) std::cout << "Error: Division by zero\n";
	else if (error_code == 9) std::cout << "Error: Arithmetic operation causes overflow\n";

}

int Rpn::checknumbers(const std::string& input)
{
    if (input.empty()) return 1;
	else if (std::isdigit(input[0])) num_count++;
	else if (input[0] == '+' || input[0] == '-'
		|| input[0] == '*' || input[0] == '/')
		op_count++;
	else if (!std::isspace(input[0])) return 2;
    for (std::size_t i = 1; i < input.size(); ++i)
    {
        if (std::isdigit(input[i]))
        {
            if (!std::isspace(input[i - 1]))
                return 3;
            std::size_t start = i;
            std::size_t end = input.find_first_not_of("0123456789", start);
            std::string numStr = input.substr(start, end - start);
			i = end - 1;
            int number = std::strtol(numStr.c_str(), NULL, 10);

            if (number < 0 || number > 9) return 4;
			num_count++;
        }
        else if (input[i] == '+' || input[i] == '-' ||
            input[i] == '*' || input[i] == '/')
        {
            if (!std::isspace(input[i - 1])) return 5;
			op_count++;
        }
        else if (std::isspace(input[i])) continue;
        else return 2;
    }
	if (op_count != (num_count - 1)) return 6;
    return 0;
}

int	isoperator(char op)
{
	if (op == '+' || op == '-' || op == '*' || op == '/') return 1;
	return 0;
}

int Rpn::processRpnExpression(const std::string& input)
{
	std::istringstream iss(input);
    std::string token;
	int	num_in_stack = 0;

    while (iss >> token)
	{
		if (isdigit(token[0]))
		{
			int number = atoi(token.c_str());
            myStack.push(number);
			num_in_stack++;
		}
		else if (isoperator(token[0]) == 1)
		{
			if (num_in_stack < 2) return 7;
			int operand2 = myStack.top();
            myStack.pop();
            int operand1 = myStack.top();
            myStack.pop();
			long result = 0;

			if (token == "+") result = static_cast<long>(operand1) + static_cast<long>(operand2);
            else if (token == "-") result = static_cast<long>(operand1) - static_cast<long>(operand2);
            else if (token == "*") result = static_cast<long>(operand1) * static_cast<long>(operand2);
            else if (token == "/")
			{
                if (operand2 == 0) return 8;
                result = operand1 / operand2;
			}
			if (result > 2147483647 || result < std::numeric_limits<int>::min())
                return 9;
			myStack.push(static_cast<int>(result));
			num_in_stack--;
		}
	}
	if (!myStack.empty()) std::cout << "Result: " << myStack.top() << std::endl;
    else std::cerr << "Error: Invalid expression" << std::endl;
	return 0;
}

