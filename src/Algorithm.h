#pragma once
#include <string>

#include "DataGenerator.h"

int PowHashed(int base, int exp, int maxHashValue);

bool FindSubStringNaive(const std::string text, const std::string subString);

int RabinKarpSubStringSearch(const std::string text, const std::string sample);

int GetStringHash(const char* start, const int hashSize);

bool AreStringsEqual(const char* text, const char* sample);

list* SearchInList(list* first, int target);

void InsertElementInList(list** first, int data);

void PrintListElements(list* first);

void EraseElementInList(list** first, int target);

list* FindPreviousElement(list* previous, int target);

int LinearSearch(int* data, int size, int value);

int BarierSearch(int* data, int size, int value);

void Boyer_MooreSubstringSearch(const std::string text, const std::string sample);