#include <iostream>
#include <math.h>

#include "Algorithm.h"

int PowInt(int base, int exp)
{
	if (exp == 1)
		return base;
	return base * PowInt(base, exp - 1);
}

bool FindSubStringNaive(const std::string text, const std::string subString)
{
	int sameCharacterCounter = 0;
	for (int enterPosition = 0; enterPosition < text.size() - subString.size(); ++enterPosition)
	{
		if (text[enterPosition] == subString[0])
		{
			sameCharacterCounter = 1;
			for (int j = 1; j < subString.size(); ++j)
			{
				if (text[(size_t)enterPosition + j] != subString[j])
				{
					sameCharacterCounter = 0;
					break;
				}
				else
				{
					sameCharacterCounter++;
				}
			}

			if (sameCharacterCounter != subString.size())
			{
				continue;
			}
			else
			{
				return true;
			}
		}
	}
	
	return false;
}

int GetStringHash(const char* start, const int stringSize, int maxHashValue)
{
	int hash = 0;
	auto alphabetSizeIncremented = (unsigned int)('a' - 'A') + 1;
	int temp = 1;

	for (int i = stringSize - 1; i > -1; --i)
	{
		hash += (temp * (unsigned int)('a' - start[i])) % maxHashValue;
		temp *= alphabetSizeIncremented;
	}

	return hash % maxHashValue;
}

bool AreStringsEqual(const char* text, const char* sample, const int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (text[i] != sample[i])
			return false;
	}
	return true;
}

int RabinKarpSubStringSearch(const std::string text, const std::string sample)
{// TODO check hash calculating
	int textSize = text.size(), sampleSize = sample.size();
	int maxHashValue = textSize;
	auto alphabetSizeIncremented = (unsigned int)('a' - 'A') + 1;
	int temp = PowInt(alphabetSizeIncremented, sampleSize);

	int sampleHash = GetStringHash(sample.c_str(), sampleSize, maxHashValue);
	int subTextHash = GetStringHash(text.c_str(), sampleSize, maxHashValue);

	for (int i = 0; i < textSize - sampleSize; ++i)
	{
		if (subTextHash == sampleHash && AreStringsEqual(text.c_str(), sample.c_str(), sampleSize))
			return i;
		subTextHash -= temp * (unsigned int)('a' - text[i]);
		subTextHash *= alphabetSizeIncremented;
		subTextHash += text[(size_t)i + sampleSize];
	}

	return -1;
}

list* SearchInList(list* first, int target)
{
	if (first == NULL)
		return NULL;

	if (first->data == target)
		return first;
	else
		return SearchInList(first->next, target);
}


void InsertElementInList(list** first, int data)
{
	list* newNode = new list;
	newNode->next = *first;
	newNode->data = data;
	*first = newNode;
}

void PrintListElements(list* first)
{
	if (first->next == NULL)
	{
		std::cout << first->data << std::endl;
		return;
	}
	else
	{
		std::cout << first->data << " ";
		PrintListElements(first->next);
	}
}

void EraseElementInList(list** first, int target)
{
	list* previous = FindPreviousElement(*first, target);
	if (previous == *first)
	{
		list* secondElement = (*first)->next;
		delete(*first);
		*first = secondElement;
	}
	else if(previous == NULL)
	{ }
	else
	{
		list* toDeleteElement = previous->next;
		previous->next = toDeleteElement->next;
		delete(toDeleteElement);
		toDeleteElement = NULL;
	}
}

list* FindPreviousElement(list* previous, int target)
{
	if (previous->next->data == target || previous->data == target)
	{
		return previous;
	}
	else if (previous->next->next == NULL)
	{
		return NULL;
	}
	else
	{
		return FindPreviousElement(previous->next, target);
	}
	// TODO Test this function
	return NULL;
}

int LinearSearch(int* data, int size, int value)
{
	for (int i = 0; i < size; ++i)
		if (data[i] == value)
			return i;
}

int BarierSearch(int* data, int size, int value)
{
	int i = 0;
	for (i = 0; data[i] != value; ++i){}

	if (i == size - 1)
		return -1;
	else
		return i;
}