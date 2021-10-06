#include <iostream>

#include "Test.h"
#include "DataGenerator.h"
#include "Algorithm.h"

int main(int argc, char** argv)
{
	//Boyer_MooreSubstringSearchTest();
	for (auto& num : GenerateRandomIntVector(-1e3, 1e3, 1e2))
		std::cout << num << std::endl;
	std::vector<int> A = { 5,2,4,6,1,3 };
	InsertionSort(A);

	std::cout << "finished" << std::endl;
	return 0;
}