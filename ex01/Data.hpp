//
// Created by Josias Mutshaila kasongo on 2023-02-07.
//

#ifndef INC_42_PISCINE_CPP06_DATA_H
#define INC_42_PISCINE_CPP06_DATA_H
#include <iostream>
#include <string>

struct Data
{
	std::string s1;
	int n;
	std::string s2;
};

uintptr_t serialize(Data* ptr);
Data* deserialize(uintptr_t raw);

#endif //INC_42_PISCINE_CPP06_DATA_H
