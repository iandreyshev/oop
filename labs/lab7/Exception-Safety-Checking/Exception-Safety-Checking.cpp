// Exception-Safety-Checking.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <cassert>

struct Data
{
	Data(int v)
		: value(v)
	{
	}
	int value = 0;
	bool throwOnComparison = false;
};

bool operator<(const Data& lhs, const Data& rhs)
{
	if (lhs.throwOnComparison || rhs.throwOnComparison)
	{
		throw std::runtime_error("something bad has happened");
	}
	return lhs.value < rhs.value;
}

bool operator==(const Data& lhs, const Data& rhs)
{
	return lhs.value == rhs.value;
}

using namespace std;

int main()
{
	Data items[] = { 5, 2, 3, 1, 4 };

	auto itMin = std::min_element(std::begin(items), std::end(items));
	if (itMin != std::end(items))
	{
		std::cout << "Min item is: " << itMin->value << "\n";
	}

	std::vector<Data> copy(begin(items), end(items));
	try
	{
		items[3].throwOnComparison = true;

		itMin = std::min_element(std::begin(items), std::end(items));

		if (itMin != std::end(items))
		{
			std::cout << "Min item is: " << itMin->value << "\n";
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
		std::vector<Data> copy2(begin(items), end(items));
		assert(copy == copy2);
	}

	return 0;
}
