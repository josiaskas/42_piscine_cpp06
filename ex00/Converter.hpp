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

		std::string convertToChar() const;
		std::string convertToInt() const;
		std::string convertToFloat() const;
		std::string convertToDouble() const;

	private:
		std::string _userInput;
		int			_int;
		char		_char;
		float		_float;
		double		_double;
		bool internalParser();
};

#endif
