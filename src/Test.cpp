#include <chrono>
#include <iostream>
#include <fstream>
#include <set>
#include <string>
#include <list>
#include <algorithm>
#include <sstream>
#include <random>

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
// with fix lenght of text and varience of lenght of sample
{
	typedef std::basic_string<char32_t> stringUTF32;
	typedef std::basic_ifstream<char32_t> u32_ifstream;

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
	for(size_t sampleSize = 4, iteration = 0; iteration < conductNumber; sampleSize += 1e4, ++iteration)
	{
		sampleSizes[iteration] = sampleSize;
		std::basic_string<char32_t> sample(sampleSize, U'ъ');
		//std::basic_string<char32_t> sample = U"Глава";

		auto beginTime = std::chrono::steady_clock::now();
		std::set<size_t> boyerIndicies = Boyer_MooreSubstringSearch(text, sample);
		//std::set<size_t> boyerIndicies = Boyer_MooreSubstringSearch(U"аакололоколокол", U"данные");
		auto endTime = std::chrono::steady_clock::now();

		boyerTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		beginTime = std::chrono::steady_clock::now();
		std::set<size_t> naiveIndicies = FindSubStringNaive(text, sample);
		endTime = std::chrono::steady_clock::now();

		bool correct = (boyerIndicies == naiveIndicies);
		naiveTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
	}

	std::ofstream resultFile;
	resultFile.open("result.txt", std::ios::out);
	resultFile << "Sample Size, " << "Boyer-Moore, " << "Naive" << std::endl;
	for (int i = 0; i < conductNumber; ++i)
		resultFile << sampleSizes[i] << " " << boyerTimes[i] << " " << naiveTimes[i] << std::endl;
	resultFile.close();
}

void BMSubstringSearch()
{
	typedef std::basic_string<char32_t> stringUTF32;
	typedef std::basic_ifstream<char32_t> u32_ifstream;
	
	stringUTF32 sample(1e6 - 2, U'р');
	
	stringUTF32 fullText(3e6, U'\0');
	
	u32_ifstream textFile;
	textFile.open("dead_souls.txt");
	if (textFile.is_open())
	{
		char32_t c;
		for (size_t textPosition = 0; textPosition < fullText.size() && textFile.get(c); ++textPosition)
			fullText[textPosition] = c;
	}
	textFile.close();

	size_t minTextSize = 1e6 - 1;
	size_t stepTextSize = 2e4;
	size_t conductNumber = (fullText.size() - minTextSize) / stepTextSize;
	double* boyerTimes = new double[conductNumber];
	double* naiveTimes = new double[conductNumber];
	size_t* textSizes = new size_t[conductNumber];
	
	for (size_t textSize = minTextSize, iteration = 0; 
		textSize < fullText.size() && iteration < conductNumber; 
		textSize += stepTextSize, ++iteration)
	{
		stringUTF32 text(fullText.begin(), fullText.begin() + textSize);
		textSizes[iteration] = textSize;
		
		//std::basic_string<char32_t> sample = U"Глава";

		auto beginTime = std::chrono::steady_clock::now();
		std::set<size_t> naiveIndicies = FindSubStringNaive(text, sample);
		auto endTime = std::chrono::steady_clock::now();

		naiveTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		beginTime = std::chrono::steady_clock::now();
		std::set<size_t> boyerIndicies = Boyer_MooreSubstringSearch(text, sample);
		endTime = std::chrono::steady_clock::now();

		boyerTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		//bool correct = (boyerIndicies == naiveIndicies);
	}

	std::ofstream resultFile;
	resultFile.open("result.txt", std::ios::out);
	resultFile << "Text Size, " << "Boyer-Moore, " << "Naive" << std::endl;
	for (int i = 0; i < conductNumber; ++i)
		resultFile << textSizes[i] << " " << boyerTimes[i] << " " << naiveTimes[i] << std::endl;
	resultFile.close();
}

void AveragingTest()
{
	size_t NumberOfExperiments = 1e2;
	size_t minTextSize = 1e6 - 1;
	size_t stepTextSize = 2e4;
	size_t conductNumber = (3e6 - minTextSize) / stepTextSize;
	std::vector<double> meanBoyerTimes(conductNumber);
	std::vector<double> meanNaiveTimes(conductNumber);
	size_t* textSizes = new size_t[conductNumber];
	for (size_t iteration = 0; iteration < NumberOfExperiments; ++iteration)
	{
		BMSubstringSearch();

		std::ifstream resultFile;
		resultFile.open("result.txt");
		for (int i = 0; i < conductNumber; ++i)
		{
			std::string line;
			std::getline(resultFile, line);
			std::istringstream ss(line);

			ss >> textSizes[i];
			double temp;
			ss >> temp;
			meanBoyerTimes[i] += temp / NumberOfExperiments;
			ss >> temp;
			meanNaiveTimes[i] += temp / NumberOfExperiments;
		}
		resultFile.close();
	}

	std::ofstream resultFile;
	resultFile.open("result.txt", std::ios::out);
	resultFile << "Text Size, " << "Mean Boyer-Moore, " << "Mean Naive" << std::endl;
	for (int i = 0; i < conductNumber; ++i)
		resultFile << textSizes[i] << " " << meanBoyerTimes[i] << " " << meanNaiveTimes[i] << std::endl;
	resultFile.close();
}

void SortingTest()
// Comparision of Insertion sort and Heap sort
{
	SortingTestWithExperimentStand();
	SortingTestWithTimeMeasurment();
}

void SortingTestWithTimeMeasurment()
{
	size_t minDataSize = 1e2, maxDataSize = 1e5, stepDataSize = 1e3;
	auto measurmentCount = (maxDataSize - minDataSize) / stepDataSize;

	std::vector<double> insertionTimes(measurmentCount);
	std::vector<double> heapTimes(measurmentCount);

	for (size_t dataSize = minDataSize, iteration = 0;
		dataSize < maxDataSize && iteration < measurmentCount;
		dataSize += stepDataSize, ++iteration)
	{
		std::vector<int> data = GenerateRandomIntVector(-1e3, 1e3, dataSize);

		std::vector<int> sample(data);
		auto beginTime = std::chrono::steady_clock::now();
		InsertionSort(sample);
		auto endTime = std::chrono::steady_clock::now();

		insertionTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		sample = std::vector<int>(data);

		beginTime = std::chrono::steady_clock::now();
		HeapSort(sample);
		endTime = std::chrono::steady_clock::now();

		heapTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
	}

	std::ofstream sortingTimeResults;
	sortingTimeResults.open("SortingTime.txt");
	sortingTimeResults << "Data Size," << "Insertion Sort," << "Heap Sort" << std::endl;
	for (size_t dataSize = minDataSize, iteration = 0; 
		dataSize < maxDataSize && iteration < measurmentCount;
		dataSize += stepDataSize, iteration++)
		sortingTimeResults << dataSize << " " << insertionTimes[iteration] << " " << heapTimes[iteration] << std::endl;
	sortingTimeResults.close();
}

void SortingTestWithExperimentStand()
{
	size_t dataSize = 1e4;
	std::vector<int> initialData = GenerateRandomIntVector(-1e3, 1e3, dataSize);

	std::list<std::vector<int>> experimentStand;
	GenerateExperimentStand(experimentStand, initialData);

	std::vector<double> insertionTimes(experimentStand.size());
	std::vector<double> heapTimes(experimentStand.size());
	size_t iteration = 0;
	for (auto& v : experimentStand)
	{
		std::vector<int> sample(v);
		auto beginTime = std::chrono::steady_clock::now();
		InsertionSort(sample);
		auto endTime = std::chrono::steady_clock::now();

		insertionTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		sample = std::vector<int>(v);
		beginTime = std::chrono::steady_clock::now();
		HeapSort(sample);
		endTime = std::chrono::steady_clock::now();

		heapTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
		++iteration;
	}

	std::ofstream expStandResults;
	expStandResults.open("SortingExperimentalStand.txt");
	expStandResults << "Sample number," << "Insertion Sort," << "Heap Sort" << std::endl;
	for (size_t sampleNum = 0; sampleNum < experimentStand.size(); ++sampleNum)
		expStandResults << sampleNum << " " << insertionTimes[sampleNum] << " " << heapTimes[sampleNum] << std::endl;
	expStandResults.close();
}

void MergesSortTest()
{
	size_t dataSize = 1023;
	std::vector<int> initialData = GenerateRandomIntVector(1e0, 1e2, dataSize);
	//std::vector<int> initialData = { 6, 3, 1, 9 };
	
	//MergeSort(initialData);
	mergesort(initialData, 0, initialData.size() - 1);
	bool isSorted = std::is_sorted(initialData.begin(), initialData.end());
}

void SalesManProblem(int cityNumber)
{
	std::vector<std::vector<float>> cityMap(cityNumber, std::vector<float>(cityNumber, 0.));
	std::vector<float> xCoord(cityNumber, 0.), yCoord(cityNumber, 0.);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(-10., 10.);

	for (size_t i = 0; i < cityNumber; i++)
	{
		xCoord[i] = distrib(gen);
		yCoord[i] = distrib(gen);
	}

	for (size_t i = 0; i < cityNumber; i++)
	{
		for (size_t j = 0; j < cityNumber; j++)
		{
			if (i == j) cityMap[i][j] = 0;
			else
			{
				auto xDiff = xCoord[i] - xCoord[j];
				auto yDiff = yCoord[i] - yCoord[j];

				auto xDiffSquared = xDiff * xDiff;
				auto yDiffSquared = yDiff * yDiff;

				auto lenght = std::sqrt(xDiffSquared + yDiffSquared);

				cityMap[i][j] = cityMap[j][i] = lenght;
			}
		}
	}


}