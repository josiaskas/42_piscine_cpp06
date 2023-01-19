/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:20:08 by jkasongo          #+#    #+#             */
/*   Updated: 2023/01/19 16:27:41 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

int main(int argc, char **argv)
{
	std::string userInput;

	if (argc != 2){
		std::cout << "usage: ./convert [number]" << std::endl;
		return 1;
	}
	userInput = argv[1];
	if (userInput.empty()){
		std::cout << "Error: empty string" << std::endl;
		return 1;
	}

	return 0;
}
