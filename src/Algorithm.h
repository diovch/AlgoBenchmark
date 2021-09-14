#pragma once
#include <string>

#include "DataGenerator.h"

int PowInt(int base, int exp);

bool FindSubStringNaive(const std::string text, const std::string subString);

int RabinKarpSubStringSearch(const std::string text, const std::string sample);

int GetStringHash(const char* start, const int size, const int hashSize);

bool AreStringsEqual(const char* text, const char* sample, const int size);

list* SearchInList(list* first, int target);

void InsertElementInList(list** first, int data);

void PrintListElements(list* first);

void EraseElementInList(list** first, int target);

list* FindPreviousElement(list* previous, int target);

int LinearSearch(int* data, int size, int value);

int BarierSearch(int* data, int size, int value);