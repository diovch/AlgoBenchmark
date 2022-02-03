#pragma once
#include <string>
#include <vector>
#include <list>

struct list
{
	int data = INT_MIN;
	struct list* next = NULL;
};

void CreateList(list* first, int* t, size_t size);

template <typename dataType = int>
struct tree
{
	dataType item;
	struct tree* parent = NULL;
	struct tree* left;
	struct tree* right;
};

std::string GenerateDNAString(size_t length);

std::basic_string<char32_t> GenerateUTF32String(size_t size);

std::vector<int> GenerateRandomIntVector(int min, int max, size_t size);

void GenerateExperimentStand(std::list<std::vector<int>>& experimentStand, std::vector<int>& initialData);

void GenerateCityMap(std::vector<std::vector<float>>& cityDistances, std::vector<float>& xCoord, std::vector<float>& yCoord);

int GenerateIntNum(int min, int max);