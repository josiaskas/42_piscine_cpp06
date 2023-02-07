/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:20:08 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/19 16:20:08 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <ctime>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base*	generate(void)
{
	int random = rand() % 3;
	if (random == 0){
		return new A();
	}
	else if (random == 1)
		return new B();
	else
		return new C();
}

void	identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "A" << std::endl;
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << std::endl;
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << std::endl;
	else
		std::cout << "Unknown" << std::endl;
}

void	identify(Base& p)
{
	try
	{
		A &a = dynamic_cast<A&>(p);
		(void)a;
		std::cout << "A" << std::endl;
	}
	catch (std::exception &e)
	{
		try
		{
			B &b = dynamic_cast<B&>(p);
			(void)b;
			std::cout << "B" << std::endl;
		}
		catch (std::exception &e)
		{
			try
			{
				C &c = dynamic_cast<C&>(p);
				(void)c;
				std::cout << "C" << std::endl;
			}
			catch (std::exception &e)
			{
				std::cout << "Unknown" << std::endl;
			}
		}
	}
}

int	main(void)
{
	srand(time(NULL));
	Base *base = generate();
	identify(base);
	identify(*base);
	delete base;
	return 0;
}