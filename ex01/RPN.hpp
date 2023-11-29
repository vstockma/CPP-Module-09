/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:16:53 by vstockma          #+#    #+#             */
/*   Updated: 2023/11/29 13:37:13 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cctype>
#include <cstdlib>
#include <sstream>
#include <string>
#include <stack>
#include <limits>

class Rpn
{
    private:
        int num_count;
        int op_count;
        std::stack<int> myStack; 
    public:
        Rpn();
        ~Rpn();
        Rpn(const Rpn& copy);
        Rpn& operator=(const Rpn& copy);

        int checknumbers(const std::string& input);
        int processRpnExpression(const std::string& input);
};

void errormessage(int error_code);

#endif