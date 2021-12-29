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

template <typename dataType>
void CreateTree(tree<dataType>* parent, dataType* t, size_t size);

template <typename dataType>
void InsertTreeElement(tree<dataType>** l, dataType item, tree<dataType>* parent);

std::string GenerateDNAString(size_t length);

std::basic_string<char32_t> GenerateUTF32String(size_t size);

std::vector<int> GenerateRandomIntVector(int min, int max, size_t size);

void GenerateExperimentStand(std::list<std::vector<int>>& experimentStand, std::vector<int>& initialData);

void GenerateCityMap(std::vector<std::vector<float>>& cityDistances, std::vector<float>& xCoord, std::vector<float>& yCoord);

int GenerateIntNum(int min, int max);

std::vector<std::vector<int>> GeneratePermutations(int n);