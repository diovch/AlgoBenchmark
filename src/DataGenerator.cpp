#include <random>
#include <string>
#include <list>

#include "DataGenerator.h"
#include "Algorithm.h"

void CreateList(list* first, int* numData, size_t size)
{
	list* temp = first;
	for (int i = 0; i < size; ++i)
	{
		temp->data = numData[i];
		if (i != size - 1)
		{
			list* newNode = new list;
			temp->next = newNode;
			temp = temp->next;
		}
	}
}

template <typename dataType>
void CreateTree(tree<dataType>* parent, dataType* data, size_t size)
{
	tree<dataType>* current = parent;
	for (int i = 0; i < size; ++i)
	{
		InsertTreeElement(&current, data[i], parent);
	}
}

template <typename dataType>
void InsertTreeElement(tree<dataType>** l, dataType item, tree<dataType>* parent)
{
	//TODO finish method
}

std::string GenerateDNAString(size_t length)
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

std::basic_string<char32_t> GenerateUTF32String(size_t size)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<uint32_t> distrib(1, UINT32_MAX);
	char32_t c = static_cast<char32_t>(UINT32_MAX-1);
	std::basic_string<char32_t> res(size, U'j');
	for (char32_t symb : res)
	{
		res = (char32_t)distrib(gen);
	}
	return res;
}

std::vector<int> GenerateRandomIntVector(int min, int max, size_t size)
{
	std::vector<int> result(size);

	std::random_device rd;  
	std::mt19937 gen(rd()); 
	std::uniform_int_distribution<> distrib(min, max);
	
	for (auto& num : result)
	{
		num = distrib(gen);
	}

	return result;
}



void GenerateExperimentStand(std::list<std::vector<int>>& experimentStand, std::vector<int>& initialData)
{
	std::vector<int> sorted(initialData.begin(), initialData.end());
	std::sort(sorted.begin(), sorted.end());

	experimentStand.push_back(initialData);
	
	std::vector<int>& minBubblePassed = GetBublePassedVector(initialData, ComparisonType::MIN);
	
	while (minBubblePassed != sorted)
	{
		minBubblePassed = GetBublePassedVector(minBubblePassed, ComparisonType::MIN);
		experimentStand.push_back(minBubblePassed);
	}

	std::vector<int>& maxBubblePassed = GetBublePassedVector(initialData, ComparisonType::MAX);
	
	sorted = std::vector<int>{ sorted.rbegin(), sorted.rend() };
	while (maxBubblePassed != sorted)
	{
		maxBubblePassed = GetBublePassedVector(maxBubblePassed, ComparisonType::MAX);
		experimentStand.push_front(maxBubblePassed);
	}
	bool mistake = (minBubblePassed == maxBubblePassed);
}

void GenerateCityMap(std::vector<std::vector<float>>& cityDistances, std::vector<float>& xCoord, std::vector<float>& yCoord)
{
	size_t cityNumber = xCoord.size();

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
			if (i == j) cityDistances[i][j] = 0;
			else
			{
				auto xDiff = xCoord[i] - xCoord[j];
				auto yDiff = yCoord[i] - yCoord[j];

				auto xDiffSquared = xDiff * xDiff;
				auto yDiffSquared = yDiff * yDiff;

				auto lenght = std::sqrt(xDiffSquared + yDiffSquared);

				cityDistances[i][j] = cityDistances[j][i] = lenght;
			}
		}
	}
}

int GenerateIntNum(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(min, max);
	return distrib(gen);
}
