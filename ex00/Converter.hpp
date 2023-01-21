/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Converter.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:28:23 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/19 16:41:12 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_HPP
# define CONVERTER_HPP
# include <iostream>
# include <string>
# include <sstream>
# include <iomanip>
# include <cmath>

class Converter
{
	public:
		Converter();
		Converter(std::string userInput);
		Converter(Converter const &src);
		virtual ~Converter();
		Converter &operator=(Converter const &src);

		char	getChar() const;
		int		getInt() const;
		float	getFloat() const;
		double	getDouble() const;
		class ImpossibleException : public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class NonDisplayableException : public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class EmptyException : public std::exception{
			public:
				virtual const char* what() const throw();
		};
		class InvalidInputException : public std::exception{
			public:
				virtual const char* what() const throw();
		};
	private:
		std::string _userInput;
		int			_int;
		char		_char;
		float		_float;
		double		_double;
		enum eType
		{
			CHAR,
			INT,
			FLOAT,
			DOUBLE,
			PSEUDO_LITERAL,
		};
		eType		_type;
		bool internalParser();
		bool isPseudoLiteral() const;
};

std::ostream &operator<<(std::ostream &o, Converter const &src);
#endif
