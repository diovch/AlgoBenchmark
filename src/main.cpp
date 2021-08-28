#include <iostream>

#include "Test.h"
#include "DataGenerator.h"
#include "Algorithm.h"

int main()
{
	auto alphabetSize = (unsigned int)('a' - 'A');
	std::string t = "cde";
	std::string s = "abcdefc";
	auto ind = RabinKarpSubStringSearch(t, s);
	auto q = GetStringHash(s.c_str(), s.size(), alphabetSize);

	std::cout << "finished" << std::endl;
	return 0;
}