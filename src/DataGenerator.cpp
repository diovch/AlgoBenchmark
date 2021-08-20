#include <random>
#include <string>

#include "DataGenerator.h"

std::string GenerateString(size_t length)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(1, 40);

	std::string result(length, ' ');

	for (int i = 0; i < length; ++i)
	{
		//Use `distrib` to transform the random unsigned int generated by gen into an int in [1, 12]
		if (distrib(gen) <= 10)
		{
			result[i] = 'a';
		}
		else if (distrib(gen) > 10 && distrib(gen) <= 20)
		{
			result[i] = 't';
		}
		else if (distrib(gen) > 20 && distrib(gen) <= 30)
		{
			result[i] = 'g';
		}
		else
		{
			result[i] = 'c';
		}
	}

	return result;
}