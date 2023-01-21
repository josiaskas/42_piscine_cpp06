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

Converter::Converter(): _userInput("0"), _int(0), _char(0), _float(0), _double(0), _error(false)
{
}

Converter::Converter(std::string userInput): _userInput(userInput), _int(0), _char(0), _float(0), _double(0), _error(false)
{
	try{
		internalParser();
	}
	catch (std::exception &e)
	{
		_error = true;
	}
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

void	Converter::internalParser()
{
	if (_userInput.empty())
		throw Converter::EmptyInputException();
	else
	{
		char	*leftCharOnLong = NULL;
		char	*leftCharOnDouble = NULL;
		long	parsedLong = strtol(_userInput.c_str(), &leftCharOnLong, 10);
		double	parsedDouble = strtod(_userInput.c_str(), &leftCharOnDouble);

		if (isPseudoLiteral())
		{
			_int = static_cast<int>(parsedDouble);
			_char = static_cast<char>(parsedDouble);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
			_type = PSEUDO_LITERAL;
		}
		else if (leftCharOnLong[0] == '\0')
		{
			if (parsedLong >= 0 && parsedLong <= 127)
				_type = CHAR;
			else if ((parsedLong < INT_MAX) && (parsedLong > INT_MIN))
				_type = INT;
			else
				_type = DOUBLE;// overflow
			_int = static_cast<int>(parsedLong);
			_char = static_cast<char>(parsedLong);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
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
			if (parsedDouble >= -FLT_MAX && parsedDouble <= FLT_MAX)
				_type = DOUBLE; // overflow
			else
				_type = FLOAT;
			_int = static_cast<int>(parsedDouble);
			_char = static_cast<char>(parsedDouble);
			_float = static_cast<float>(parsedDouble);
			_double = static_cast<double>(parsedDouble);
		}
		else
			throw Converter::InvalidInputException();
	}
}

char Converter::getChar() const
{
	if (_error)
		throw Converter::ImpossibleException();
	if (_type == CHAR)
	{
		if (isprint(_char))
			return _char;
		else
			throw Converter::NonDisplayableException();
	}
	else if (_type == INT)
	{
		if (isprint(_int))
			return _char;
		else if (isascii(_char))
			throw Converter::NonDisplayableException();
		else
			throw Converter::ImpossibleException();
	}
	else if (_type == FLOAT)
	{
		if (_float >= 0 && _float <= 127)
		{
			if (isprint(_char))
				return _char;
			else
				throw Converter::NonDisplayableException();
		}
		else
			throw Converter::ImpossibleException();
	}
	else if (_type == DOUBLE)
	{
		if (_double >= 0 && _double <= 127)
		{
			if (isprint(_char))
				return static_cast<char>(65);
			else
				throw Converter::NonDisplayableException();
		}
		else
			throw Converter::ImpossibleException();
	}
	else
		throw Converter::ImpossibleException();
}

int Converter::getInt() const
{
	if (_error)
		throw Converter::ImpossibleException();
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
	else
		throw Converter::ImpossibleException();
}

float Converter::getFloat() const
{
	if (_error)
		throw Converter::ImpossibleException();
	if (_type == CHAR)
		return static_cast<float>(_char);
	else if (_type == INT)
		return static_cast<float>(_int);
	else if (_type == FLOAT)
		return _float;
	else if (_type == DOUBLE)
	{
		if (_double >= -FLT_MAX && _double <= FLT_MAX)
			return static_cast<float>(_double);
		else
			throw Converter::ImpossibleException();
	}
	else if (_type == PSEUDO_LITERAL)
		throw Converter::NonDisplayableException();
	else
		throw Converter::ImpossibleException();
}

double Converter::getDouble() const
{
	if (_error)
		throw Converter::ImpossibleException();
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
		throw Converter::ImpossibleException();
}

bool Converter::isPseudoLiteral() const
{
	if (_userInput == "nan" || _userInput == "nanf" || _userInput == "+inf" || _userInput == "+inff" || _userInput == "-inf" || _userInput == "-inff")
		return true;
	else
		return false;
}

const char *Converter::InvalidInputException::what() const throw()
{
	return "Invalid input";
}

const char *Converter::NonDisplayableException::what() const throw()
{
	return "Non displayable";
}

const char *Converter::ImpossibleException::what() const throw()
{
	return "impossible";
}

const char *Converter::EmptyInputException::what() const throw()
{
	return "Empty input";
}

void Converter::printChar(std::ostream &out) const{
	out << "char: ";
	try
	{
		char c = getChar();
			out << "'" << c << "'" << "\n";
	}
	catch (const std::exception &e)
	{
		out << e.what() << "\n";
	}
}

void Converter::printInt(std::ostream &out) const{
	out << "int: ";
	try
	{
		int i = getInt();
		out << i << "\n";
	}
	catch (const std::exception &e)
	{
		out << e.what() << "\n";
	}
}

void Converter::printFloat(std::ostream &out) const{
	out << "float: ";
	try
	{
		float f = getFloat();
		out << std::fixed << std::setprecision(1) << f << "f" << "\n";
	}
	catch (const std::exception &e)
	{
		if (_type == PSEUDO_LITERAL)
			out << _float << "f" << "\n";
		else
			out << e.what() << "\n";
	}
}

void Converter::printDouble(std::ostream &out) const{
	out << "double: ";
	try
	{
		double d = getDouble();
		out << std::fixed << std::setprecision(1) << d << std::endl;
	}
	catch (const std::exception &e)
	{
		if (_type == PSEUDO_LITERAL)
			out << _double << std::endl;
		else
			out << e.what() << std::endl;
	}
}

std::ostream &operator<<(std::ostream &out, Converter const &converter)
{
	converter.printChar(out);
	converter.printInt(out);
	converter.printFloat(out);
	converter.printDouble(out);
	return out;
}




