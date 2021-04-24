#include <chrono>
#include <iostream>

#include "Test.h"
#include "DataGenerator.h"
#include "Algorithm.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;

void TestTask()
{
	size_t textLength = 0, subStringLength = 0;
	std::cin >> textLength >> subStringLength;

	const std::string& text = GenerateString(textLength);
	const std::string subString = GenerateString(subStringLength);
	//const std::string text = "atgccgta";
	//const std::string subString = "ccgt";

	auto t1 = high_resolution_clock::now();
	FindSubStringNaive(text, subString);
	auto t2 = high_resolution_clock::now();

	/* Getting number of milliseconds as a double. */
	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << ms_double.count() << std::endl;
}