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

#include "Data.hpp"
#include <iomanip>

uintptr_t serialize(Data* ptr)
{
	return reinterpret_cast<uintptr_t>(ptr);
}

Data* deserialize(uintptr_t raw)
{
	return reinterpret_cast<Data*>(raw);
}

int	main(void)
{
	Data	*data = new Data();
	data->s1 = "Hello";
	data->n = 42;
	data->s2 = "World";

	std::cout << "data->s1: " << data->s1 << std::endl;
	std::cout << "data->n: " << data->n << std::endl;
	std::cout << "data->s2: " << data->s2 << std::endl;

	uintptr_t raw = serialize(data);
	Data *data2 = deserialize(raw);

	std::cout << "data2->s1: " << data2->s1 << std::endl;
	std::cout << "data2->n: " << data2->n << std::endl;
	std::cout << "data2->s2: " << data2->s2 << std::endl;

	std::cout << "pointer data: " << &data << std::endl;
	std::cout << "pointer data2: " << &data2 << std::endl;

	delete data;
	return 0;
}

