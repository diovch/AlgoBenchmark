#pragma once
#include <string>
#include <set>
#include <vector>

#include "DataGenerator.h"

int PowHashed(int base, int exp, int maxHashValue);

std::set<size_t> FindSubStringNaive(const std::basic_string<char32_t>& text, const std::basic_string<char32_t>& sample);

int RabinKarpSubStringSearch(const std::string& text, const std::string& sample);

int GetStringHash(const char* start, int size, int maxHashValue);

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