#pragma once

#include <string>
#include <set>
#include <vector>
#include <list>

#include "DataGenerator.h"

int PowHashed(int base, int exp, int maxHashValue);

std::set<size_t> FindSubStringNaive(const std::basic_string<char32_t>& text, const std::basic_string<char32_t>& sample);

int RabinKarpSubStringSearch(const std::string& text, const std::string& sample);

unsigned int GetStringHash(const char* start, int size, int maxHashValue);

unsigned int GetStringHash(const wchar_t* start, unsigned int size, unsigned int maxHashValue);

int GetNaiveStringHash(std::string& str);

bool AreStringsEqual(const char* text, const char* sample);

list* SearchInList(list* first, int target);

void InsertElementInList(list** first, int data);

void PrintListElements(list* first);

void EraseElementInList(list** first, int target);

list* FindPreviousElement(list* previous, int target);

int LinearSearch(int* data, int size, int value);

int BarierSearch(int* data, int size, int value);

std::set<size_t> Boyer_MooreSubstringSearch(const std::basic_string<char32_t>& text, const std::basic_string<char32_t>& sample);

void swap(int* a, int* b);

void InsertionSort(std::vector<int>& dataArray);

enum ComparisonType
{
	MIN,
	MAX
};

unsigned long DanBernsteinHash(unsigned char* str);

std::string GenerateRandomString(int size);

std::vector<int> GetBublePassedVector(std::vector<int>& v, enum ComparisonType compType);

size_t GetParent(size_t i);
size_t GetLeft(size_t i);
size_t GetRight(size_t i);

void Heapify(std::vector<int>& dataArray, size_t heapsize, size_t rootInd);

void HeapSort(std::vector<int>& dataArray);

void mergesort(std::vector<int>& data, int l, int r);

void merge(std::vector<int>& data, int l, int m, int r);


void perm(std::vector<int>& cityIndicies, std::vector<std::vector<float>>& cityDistances, int lf, float* minDistance, size_t* count);

float dist(std::vector<int>& ar, std::vector<std::vector<float>>& dists);

void print(std::vector<int>& ar, std::vector<std::vector<float>>& dists);

void swap(std::vector<int>& ar, int i, int j);

void QuickSort(std::vector<int>& ar, int low, int high);

void MultiPhaseSort(std::vector<int>& ar);

void DFS(int cityIndex, std::vector<std::vector<bool>>& isRoadExists, std::vector<bool>& used);

bool IsOneComponent(std::vector<std::vector<bool>>& isRoadExists);

int GetNumberOfConnections(std::vector<std::vector<bool>>& isRoadExists);

float GetMinDistance(std::vector<std::vector<float>>& cityDistances, std::vector<std::vector<bool>>& isRoadExists, int& count);
