#pragma once
#include <string>

#include "DataGenerator.h"

bool FindSubStringNaive(const std::string text, const std::string subString);

list* SearchInList(list* first, int target);

void CreateList(list *first, int *t, size_t size);

void InsertElementInList(list** first, int data);

void PrintListElements(list* first);

void EraseElementInList(list** first, int target);

list* FindPreviousElement(list* previous, int target);