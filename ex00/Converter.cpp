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

void Converter::internalParser()
{
	if (_userInput.empty())
		throw Converter::EmptyInputException();
	else if (_userInput.size() == 1)
	{
		if (isdigit(_userInput[0]))
		{
			_int = static_cast<int>(_userInput[0]);
			_char = static_cast<char>(_userInput[0]);
			_float = static_cast<float>(_userInput[0]);
			_double = static_cast<double>(_userInput[0]);
			_type = INT;
		}
		else
		{
			_int = static_cast<int>(_userInput[0]);
			_char = static_cast<char>(_userInput[0]);
			_float = static_cast<float>(_userInput[0]);
			_double = static_cast<double>(_userInput[0]);
			_type = CHAR;
		}
	}
	else
	{
		char	*leftCharOnLong = NULL;
		char	*leftCharOnDouble = NULL;
		long	parsedLong = strtol(_userInput.c_str(), &leftCharOnLong, 10);
		double	parsedDouble = strtod(_userInput.c_str(), &leftCharOnDouble);

		if (leftCharOnLong[0] == '\0')
		{
			_int = static_cast<int>(parsedLong);
			_char = static_cast<char>(parsedLong);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
			_type = INT;
		}
		else if (leftCharOnDouble[0] == '\0')
		{
			_int = static_cast<int>(parsedDouble);
			_char = static_cast<char>(parsedDouble);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
			_type = DOUBLE;
		}
		else if (leftCharOnDouble[0] == 'f' && leftCharOnDouble[1] == '\0')
		{
			_int = static_cast<int>(parsedDouble);
			_char = static_cast<char>(parsedDouble);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
			_type = FLOAT;
		}
		else if (isPseudoLiteral())
		{
			_int = static_cast<int>(parsedDouble);
			_char = static_cast<char>(parsedDouble);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
			_type = PSEUDO_LITERAL;
		}
		else
			throw Converter::InvalidInputException();
	}
}

char Converter::getChar() const
{
	if (_type == CHAR)
	{
		if (isprint(_char))
			return _char;
		else
			throw Converter::NonDisplayableException();
	}
	else if (_type == INT)
	{
		if (_int >= 0 && _int <= 127)
			return static_cast<char>(_int);
		else
			throw Converter::NonDisplayableException();
	}
	else if (_type == FLOAT)
	{
		if (_float >= 0 && _float <= 127)
			return static_cast<char>(_float);
		else if (_float > 127)
			throw Converter::ImpossibleException();
		else
			throw Converter::NonDisplayableException();
	}
	else if (_type == DOUBLE)
	{
		if (_double >= 0 && _double <= 127)
			return static_cast<char>(_double);
		else if (_double > 127)
			throw Converter::ImpossibleException();
		else
			throw Converter::NonDisplayableException();
	}
	else if (_type == PSEUDO_LITERAL)
		throw Converter::NonDisplayableException();
	else
		throw Converter::InvalidInputException();
}

int Converter::getInt() const
{
	if (_type == CHAR)
		return static_cast<int>(_char);
	else if (_type == INT)
		return _int;
	else if (_type == FLOAT)
	{
		if (_float >= INT_MIN && _float <= INT_MAX)
			return static_cast<int>(_float);
		else
			throw Converter::ImpossibleException();
	}
	else if (_type == DOUBLE)
	{
		if (_double >= INT_MIN && _double <= INT_MAX)
			return static_cast<int>(_double);
		else
			throw Converter::ImpossibleException();
	}
	else if (_type == PSEUDO_LITERAL)
		throw Converter::NonDisplayableException();
	else
		throw Converter::InvalidInputException();
}

float Converter::getFloat() const
{
	if (_type == CHAR)
		return static_cast<float>(_char);
	else if (_type == INT)
		return static_cast<float>(_int);
	else if (_type == FLOAT)
		return _float;
	else if (_type == DOUBLE)
		return static_cast<float>(_double);
	else if (_type == PSEUDO_LITERAL)
		throw Converter::NonDisplayableException();
	else
		throw Converter::InvalidInputException();
}

double Converter::getDouble() const
{
	if (_type == CHAR)
		return static_cast<double>(_char);
	else if (_type == INT)
		return static_cast<double>(_int);
	else if (_type == FLOAT)
		return static_cast<double>(_float);
	else if (_type == DOUBLE)
		return _double;
	else if (_type == PSEUDO_LITERAL)
		throw Converter::NonDisplayableException();
	else
		throw Converter::InvalidInputException();
}

bool Converter::isPseudoLiteral() const
{
	if (_userInput == "nan" || _userInput == "nanf" || _userInput == "+inf" || _userInput == "+inff" || _userInput == "-inf" || _userInput == "-inff")
		return true;
	else
		return false;
}

void Converter::printChar() const
{
	try
	{
		std::cout << "char: ";
		std::cout << "'" << getChar() << "'" << std::endl;
	}
	catch (Converter::NonDisplayableException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (Converter::InvalidInputException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Converter::printInt() const
{
	try
	{
		std::cout << "int: ";
		std::cout << getInt() << std::endl;
	}
	catch (Converter::ImpossibleException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (Converter::InvalidInputException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Converter::printFloat() const
{
	try
	{
		std::cout << "float: ";
		std::cout << std::fixed << std::setprecision(1) << getFloat() << "f" << std::endl;
	}
	catch (Converter::NonDisplayableException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (Converter::InvalidInputException &e)
	{
		std::cout << e.what() << std::endl;
	}
}

void Converter::printDouble() const
{
	try
	{
		std::cout << "double: ";
		std::cout << std::fixed << std::setprecision(1) << getDouble() << std::endl;
	}
	catch (Converter::NonDisplayableException &e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (Converter::InvalidInputException &e)
	{
		std::cout << e.what() << std::endl;
	}
}





