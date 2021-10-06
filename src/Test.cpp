#include <chrono>
#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include "Test.h"
#include "DataGenerator.h"
#include "Algorithm.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration;

void FindSubStringNaiveTest()
{
	size_t textLength = 0, subStringLength = 0;
	std::cin >> textLength >> subStringLength;

	//const std::string& text = GenerateString(textLength);
	//const std::string subString = GenerateString(subStringLength);
	const std::basic_string<char32_t> text = U"atgccgta";
	const std::basic_string<char32_t> subString = U"ccgt";

	auto t1 = high_resolution_clock::now();
	FindSubStringNaive(text, subString);
	auto t2 = high_resolution_clock::now();

	/* Getting number of milliseconds as a double. */
	duration<double, std::milli> ms_double = t2 - t1;
	std::cout << ms_double.count() << std::endl;
}

void SearchInListTest()
{
	const int target = 6;
	const size_t size = 5;
	int t[size] = { 1, 3, 5, 6, 6 };
	
	list* first = new list;
	CreateList(first, t, size);

	list* result = SearchInList(first, target);
	if (result == NULL)
	{
		std::cout << "No element found";
	}
	else
	{
		std::cout << "Element is found at follow reference " << result;
	}
}

void InsertElementInListTest()
{
	list* first = new list;
	const int newData = 1000;
	const size_t size = 5;
	int t[size] = { 0, -23, 56, 32, 54 };
	CreateList(first, t, size);

	PrintListElements(first);
	InsertElementInList(&first, newData);
	PrintListElements(first);
}

void EraseElementInListTest()
{
	list* first = new list;
	const size_t size = 5;
	int t[size] = { 0, -23, 56, 32, 54 };
	const int deleteTarget = INT_FAST16_MAX;
	CreateList(first, t, size);

	PrintListElements(first);
	EraseElementInList(&first, deleteTarget);
	PrintListElements(first);
}

void SearchElementInArrayTest()
{
	int targetValue = 1024;
	size_t minDataSize = 10;
	size_t maxDataSize = 1e9;
	size_t step = 1e7;
	size_t conductNumber = (maxDataSize - minDataSize) / step;
	size_t* dataSizes = new size_t[conductNumber];
	double* linearTimes = new double[conductNumber];
	double* barierTimes = new double[conductNumber];

	for (size_t size = minDataSize, iteration = 0; iteration < conductNumber; size += step, ++iteration)
	{
		dataSizes[iteration] = size;
		int* data = new int[size + 1]; // index: 0...size, not (size - 1)
		data[size - 1] = data[size] = targetValue;
		for (int i = 0; i < size - 2; ++i)
			data[i] = 100; // chunk value


		auto beginTime = high_resolution_clock::now();
		int linearIndex = LinearSearch(data, size, targetValue);
		auto endTime = high_resolution_clock::now();

		linearTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		beginTime = high_resolution_clock::now();
		int barierIndex = BarierSearch(data, size + 1, targetValue);
		endTime = high_resolution_clock::now();

		barierTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
		
		if (linearIndex != barierIndex)
			std::cout << "insert indecies are not equal!!!" << std::endl;
		
		delete[] data;
	}

	std::ofstream f;

	f.open("experiment.txt", std::ios::out);
	if (f.is_open())
		for (int i = 0; i < conductNumber; ++i)
			f << dataSizes[i] << " " << linearTimes[i] << " " << barierTimes[i] << std::endl;
	f.close();

	delete[] dataSizes, linearTimes, barierTimes;
}

void RabinKarpSubStringSearchTest()
{
	std::string sample = "ada";
	std::string text = "bracadabr";

	auto beginTime = high_resolution_clock::now();
	int i = RabinKarpSubStringSearch(text, sample);
	auto endTime = high_resolution_clock::now();

	auto d = duration<double, std::milli>{ endTime - beginTime }.count();
}

void Boyer_MooreSubstringSearchTest()
{
	typedef std::basic_string<char32_t> stringUTF32;
	typedef std::basic_ifstream<char32_t> u32_ifstream;

	//stringUTF32 sample = U"Уыртр";
	stringUTF32 text(3e6, '\0');

	u32_ifstream textFile;
	textFile.open("dead_souls.txt");
	if (textFile.is_open())
	{
		char32_t c;
		for (size_t textPosition = 0; textPosition < text.size() && textFile.get(c); ++textPosition)
			text[textPosition] = c;
	}
	textFile.close();

	size_t count = 0;
	for (size_t i = 0; text[i] != U'\0'; ++i)
		count++;

	size_t conductNumber = 200;
	double* boyerTimes = new double[conductNumber];
	double* naiveTimes = new double[conductNumber];
	size_t* sampleSizes = new size_t[conductNumber];
	for(size_t sampleSize = 4, iteration = 0; iteration < conductNumber; sampleSize += 10000, ++iteration)
	{
		sampleSizes[iteration] = sampleSize;
		std::basic_string<char32_t> sample(sampleSize, U'р');
		//std::basic_string<char32_t> sample = U"Уыртр";

		auto beginTime = std::chrono::steady_clock::now();
		std::set<size_t> boyerIndicies = Boyer_MooreSubstringSearch(text, sample);
		auto endTime = std::chrono::steady_clock::now();

		boyerTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		beginTime = std::chrono::steady_clock::now();
		std::set<size_t> naiveIndicies = FindSubStringNaive(text, sample);
		endTime = std::chrono::steady_clock::now();

		//bool correct = (boyerIndicies == naiveIndicies);
		naiveTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
	}

	std::ofstream resultFile;
	resultFile.open("result.txt", std::ios::out);
	for (int i = 0; i < conductNumber; ++i)
		resultFile << sampleSizes[i] << " " << boyerTimes[i] << " " << naiveTimes[i] << std::endl;
	resultFile.close();
}