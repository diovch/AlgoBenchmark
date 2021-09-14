#include <chrono>
#include <iostream>
#include <fstream>

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
	const std::string text = "atgccgta";
	const std::string subString = "ccgt";

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
	int minDataSize = 1e3;
	int maxDataSize = 1e7;
	int step = 1e3;
	const int conductNumber = (maxDataSize - minDataSize) / step;
	size_t* sizes = new size_t[conductNumber];
	double* linearTimes = new double[conductNumber];
	double* barierTimes = new double[conductNumber];

	for (size_t size = minDataSize, iteration = 0; size < maxDataSize; size += step, ++iteration)
	{
		sizes[iteration] = size;
		int* data = new int[size + 1]; // index: 0...size, not (size - 1)
		data[size - 1] = data[size] = targetValue;

		auto beginTime = high_resolution_clock::now();
		int linearIndex = LinearSearch(data, size, targetValue);
		auto endTime = high_resolution_clock::now();

		linearTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		beginTime = high_resolution_clock::now();
		int barierIndex = BarierSearch(data, size + 1, targetValue);
		endTime = high_resolution_clock::now();

		barierTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		delete[] data;
	}

	std::ofstream f;

	f.open("experiment.txt", std::ios::out);
	if (f.is_open())
		for (int i = 0; i < conductNumber; ++i)
			f << sizes[i] << " " << linearTimes[i] << " " << barierTimes[i] << std::endl;
	f.close();

	delete[] sizes, linearTimes, barierTimes;
}