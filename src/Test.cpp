#include <chrono>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <string>
#include <list>
#include <algorithm>
#include <sstream>
#include <random>
#include <numeric>

#include "Test.h"
#include "DataGenerator.h"
#include "Algorithm.h"
#include "RBTree.h"
#include "TwoThreeTree.h"
#include "2_3tree.h"
#include "SalesMan.h"

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
	for(size_t sampleSize = 4, iteration = 0; iteration < conductNumber; sampleSize += 1e3, ++iteration)
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
// with fix lenght of sample and varience of lenght of text
{
	typedef std::basic_string<char32_t> stringUTF32;
	typedef std::basic_ifstream<char32_t> u32_ifstream;
	
	stringUTF32 sample(1e3 - 2, U'р');
	
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
{
	SortingTestWithTimeMeasurment();
	SortingTestWithExperimentStand();
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
		MultiPhaseSort(sample);
		auto endTime = std::chrono::steady_clock::now();

		insertionTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		sample = std::vector<int>(data);

		beginTime = std::chrono::steady_clock::now();
		mergesort(sample, 0, sample.size() - 1);
		endTime = std::chrono::steady_clock::now();

		heapTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
	}

	std::ofstream sortingTimeResults;
	sortingTimeResults.open("SortingTime.txt");
	sortingTimeResults << "Data Size," << "Multiphase Sort," << "Merge Sort" << std::endl;
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
		MultiPhaseSort(sample);
		auto endTime = std::chrono::steady_clock::now();

		insertionTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();

		sample = std::vector<int>(v);
		beginTime = std::chrono::steady_clock::now();
		mergesort(sample, 0, sample.size() - 1);
		endTime = std::chrono::steady_clock::now();

		heapTimes[iteration] = duration<double, std::milli>{ endTime - beginTime }.count();
		++iteration;
	}

	std::ofstream expStandResults;
	expStandResults.open("SortingExperimentalStand.txt");
	expStandResults << "Sample number," << "Multiphase Sort," << "Merge Sort" << std::endl;
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


void SalesManProblem(int maxCityNumber)
{
	auto minCityNumber = 3;
	std::vector<int> counts(maxCityNumber - minCityNumber + 1), cityNumbers(maxCityNumber - minCityNumber + 1);
	for (int cityNumber = minCityNumber; cityNumber <= maxCityNumber; cityNumber++)
	{
		std::vector<std::vector<float>> cityDistances(cityNumber, std::vector<float>(cityNumber, 0.));
		std::vector<float> xCoord(cityNumber, 0.), yCoord(cityNumber, 0.);

		GenerateCityMap(cityDistances, xCoord, yCoord);

		std::vector<int> cityIndicies(cityNumber);

		std::vector<bool> used(cityNumber, false);
		float minDistance = FLT_MAX;
		size_t routeCount = 0;

		rec(cityDistances, cityIndicies, used, minDistance, 1, cityNumber, 0., routeCount);

		std::cout << routeCount << " attempts" << std::endl;
		counts[cityNumber - minCityNumber] = routeCount;
		cityNumbers[cityNumber - minCityNumber] = cityNumber;
		std::cout << minDistance << " distance" << std::endl;
	}

	std::ofstream resultStream;
	resultStream.open("one_dependency.txt");
	resultStream << "City number," << "Route proposals" << std::endl;
	for (size_t i = 0; i < counts.size(); ++i)
		resultStream << cityNumbers[i] << " " << counts[i]<< std::endl;
	resultStream.close();
}

void SalesManProblemConnectivity(int cityNumber)
{
	std::vector<std::vector<float>> cityDistances(cityNumber, std::vector<float>(cityNumber, 0.));
	std::vector<float> xCoord(cityNumber, 0.), yCoord(cityNumber, 0.);
	GenerateCityMap(cityDistances, xCoord, yCoord);

	std::vector<std::vector<bool>> isRoadExists(cityNumber, std::vector<bool>(cityNumber, false));
	int totalNumberOfConnections = cityNumber * (cityNumber - 1) / 2;

	while (!IsOneComponent(isRoadExists))
	{
		int i = 0, j = 0;
		while (i == j || isRoadExists[i][j])
		{
			i = GenerateIntNum(0, cityNumber - 1);
			j = GenerateIntNum(0, cityNumber - 1);
		}
		isRoadExists[j][i] = isRoadExists[i][j] = true;
	}
	// тут будет достигнута минимальная связность

	std::vector<float> minDistances, connectivityFactor;
	std::vector<int> counts;
	int currentNumOfConnections = GetNumberOfConnections(isRoadExists);

	while (currentNumOfConnections != totalNumberOfConnections)
	{
		int count = 0;
		minDistances.push_back(GetMinDistance(cityDistances, isRoadExists, count));
		counts.push_back(count);
		connectivityFactor.push_back((float)currentNumOfConnections / totalNumberOfConnections);

		int i = 0, j = 0;
		while (i == j || isRoadExists[i][j])
		{
			i = GenerateIntNum(0, cityNumber - 1);
			j = GenerateIntNum(0, cityNumber - 1);
		}
		
		isRoadExists[j][i] = isRoadExists[i][j] = true;
		currentNumOfConnections++;
	}


	std::ofstream resultStream;
	resultStream.open("one_dependency.txt");
	resultStream << "Connectivity factor," << "Counts" << std::endl;
	for (size_t i = 0; i < minDistances.size(); ++i)
		resultStream << connectivityFactor[i] << " " << counts[i] << std::endl;
	resultStream.close();
}



void TreeComparision()
{
	size_t MegaByte = 1024 * 1024;
	size_t bufferSize = 13 * MegaByte;  // all file is 14 Mb
	std::wstring wordBuffer(bufferSize, '\0');

	std::ifstream wordStream;
	wordStream.open("HarryPotterBooks.txt");
	size_t textPosition = 0;
	if (wordStream.is_open())
	{
		char sym;

		while(wordStream && textPosition < wordBuffer.size())
		{
			wordStream.get(sym);
			wordBuffer[textPosition] = sym;
			textPosition++;
		}
	}
	wordStream.close();

	std::vector<float> textSizes;
	std::vector<float> timesRedBlack, timeTwoThree;

	for (size_t textSize = 1 * MegaByte; 
		textSize < wordBuffer.size(); 
		textSize += 0.2 * MegaByte)
	{
		std::wstring wordSubBuffer(wordBuffer.begin(), wordBuffer.begin() + textSize);
		textSizes.push_back((float)textSize / MegaByte);

		RBTree<std::wstring> RedBlackTree;
		//std::map<std::string, size_t> mapTree;
		std::wistringstream RBstream(wordSubBuffer);

		auto beginTime = std::chrono::steady_clock::now();
		while (RBstream)
		{
			std::wstring temp;
			RBstream >> temp;

			//auto it = mapTree.find(temp);
			//if (it != mapTree.end())
			//	(*it).second++;
			//else
			//	mapTree[temp] = 1;

			auto foundNode = RedBlackTree.search(temp);
			if (foundNode)
				foundNode->occurenceFrequency++;
			else
				RedBlackTree.insert(temp);
		}
		auto endTime = std::chrono::steady_clock::now();
		auto t1 = duration<float, std::milli>{ endTime - beginTime }.count();
		timesRedBlack.push_back(t1);
		//RedBlackTree.~RBTree();

		tree2_3::Tree<std::wstring> tree23;
		std::wistringstream stream23(wordSubBuffer);

		beginTime = std::chrono::steady_clock::now();
		while (stream23)
		{
			std::wstring temp;
			stream23 >> temp;

			auto wantedElement = tree23.find(temp);
			if (wantedElement)
				wantedElement->frequency++;
			else
				tree23.insert(temp);
		}
		endTime = std::chrono::steady_clock::now();
		auto t2 = duration<float, std::milli>{ endTime - beginTime }.count();
		timeTwoThree.push_back(t2);
		//tree23.~Tree();

		//std::istringstream TwoThreeStream(wordSubBuffer);
		//std::string firstWord; TwoThreeStream >> firstWord;

		//TwoThreeNode* root = new TwoThreeNode(GetNaiveStringHash(firstWord));
		//auto wordCounter = 0;
		//beginTime = std::chrono::steady_clock::now();
		//while (TwoThreeStream)
		//{
		//	std::string temp;
		//	TwoThreeStream >> temp;
		//	wordCounter++;

		//	auto foundNode = search(root, GetNaiveStringHash(temp));
		//	if (foundNode)
		//		foundNode->occurenceFrequency++;
		//	else
		//	{
		//		root = insert(root, GetNaiveStringHash(temp));
		//	}
		//}
		//endTime = std::chrono::steady_clock::now();
		//auto t2 = duration<float, std::milli>{ endTime - beginTime }.count();
		//timeTwoThree.push_back(t2);
		//removeAll(root);

	}

	std::ofstream resultStream;
	resultStream.open("result.txt");
	resultStream << "Text size (Mb)," << "Red Black Tree," << "2-3 Tree" << std::endl;
	for (size_t i = 0; i < timesRedBlack.size(); ++i)
		resultStream << textSizes[i] << " " << timesRedBlack[i] << " " << timeTwoThree[i] << std::endl;
	resultStream.close();
}



void TestDanBernsteinHash()
{
	size_t MegaByte = 1024 * 1024;
	size_t bufferSize = 2 * MegaByte;  // all file is 14 Mb
	std::wstring wordBuffer(bufferSize, '\0');

	std::ifstream wordStream;
	wordStream.open("WorldAndPeace.txt");
	size_t textPosition = 0;
	if (wordStream.is_open())
	{
		char sym;

		while (wordStream && textPosition < wordBuffer.size())
		{
			wordStream.get(sym);
			wordBuffer[textPosition] = sym;
			textPosition++;
		}
	}
	wordStream.close();

	std::wistringstream ss(wordBuffer);
	//std::istringstream ss(wordBuffer);
	std::set<std::wstring> uniqueWords;
	while (ss)
	{
		std::wstring temp;
		ss >> temp;
		uniqueWords.insert(temp);
	}
		
	auto hashSize = uniqueWords.size(); // 33981
	hashSize = 33997;

	std::vector<std::list<std::pair<std::wstring, int>>> hashTable(hashSize);
	std::wistringstream allWordStream(wordBuffer);
	std::vector<float> occupancy(hashSize);
	std::vector<int> collisions(hashSize);
	auto currentOccupancy = occupancy.begin();
	auto currentCollistionCount = collisions.begin();
	int insertedKeyCount = 0, numberOfColiisions = 0;
	while (allWordStream && currentCollistionCount < collisions.end() && currentOccupancy < occupancy.end())
	{
		std::wstring temp;
		allWordStream >> temp;

		auto hash = GetStringHash(temp.c_str(), temp.size(), hashSize);
		std::list<std::pair<std::wstring, int>>& hashedList = hashTable[hash];
		bool found = false;

		for (auto& keyFrequency : hashedList)
		{
			if (keyFrequency.first == temp)
			{
				keyFrequency.second++;
				found = true;
				break;
			}
		}

		if (!found)
		{
			hashedList.push_back({ temp, 1 });
			if(hashedList.size() > 1)
				numberOfColiisions++;
		}
		insertedKeyCount++;

		*currentOccupancy = (float)insertedKeyCount / hashSize; currentOccupancy++;
		*currentCollistionCount = numberOfColiisions; currentCollistionCount++;
	}




	
	/*std::vector<bool> isHashOccured(hashSize, false);

	int insertedKeyCount = 0, numberOfColiisions = 0;

	for (auto& word : uniqueWords)
	{
		auto hash = GetStringHash(word.c_str(), word.size(), hashSize);

		if (isHashOccured[hash])
			numberOfColiisions++;
		else
			isHashOccured[hash] = true;

		insertedKeyCount++;
		*currentOccupancy = (float)insertedKeyCount / hashSize; currentOccupancy++;
		*currentCollistionCount = numberOfColiisions; currentCollistionCount++;
	}*/

	std::ofstream resultStream;
	resultStream.open("one_dependency.txt");
	resultStream << "Occupancy," << "Collision number" << std::endl;
	for (size_t i = 0; i < occupancy.size(); ++i)
		resultStream << occupancy[i] << " " << collisions[i] << std::endl;
	resultStream.close();
}

float CollisionMeasurment(std::vector<bool>& is_occupied)
{
	auto numberOfExperiment = 1;
	std::vector<float> history(numberOfExperiment);

	for (int i = 0; i < numberOfExperiment; i++)
	{
		std::vector<bool> tempIsOccupied(is_occupied);
		float newCollisionNumber = 0;
		auto totalInserts = 100;

		for (int i = 0; i < totalInserts; i++)
		{
			std::string newTemp;
			newTemp = GenerateRandomString(GenerateIntNum(2, 10));
			auto newHashKey = GetStringHash(newTemp.c_str(), newTemp.size(), is_occupied.size());

			if (!tempIsOccupied[newHashKey])
				tempIsOccupied[newHashKey] = true;
			else
				newCollisionNumber++;
		}
		history[i] = newCollisionNumber;
	}

	return std::accumulate(history.begin(), history.end(), 0) / history.size();
}