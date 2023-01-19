/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Converter.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:32:23 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/19 16:42:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Converter.hpp"

Converter::Converter(): _userInput("0"), _int(0), _char(0), _float(0), _double(0)
{
	internalParser();
}

Converter::Converter(std::string userInput): _userInput(userInput), _int(0), _char(0), _float(0), _double(0)
{
	internalParser();
}

Converter::Converter(Converter const &src): _userInput(src._userInput), _int(src._int), _char(src._char), _float(src._float), _double(src._double)
{
	*this = src;
}

Converter::~Converter()
{
}

Converter &Converter::operator=(Converter const &src)
{
	if (this != &src)
	{
		this->_userInput = src._userInput;
		this->_int = src._int;
		this->_char = src._char;
		this->_float = src._float;
		this->_double = src._double;
	}
	return *this;
}


