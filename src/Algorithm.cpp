#include <iostream>
#include <math.h>
#include <set>

#include "Algorithm.h"

int PowHashed(int base, int exp, int maxHashValue)
{
	int res = 1;
	for (int i = 0; i < exp; ++i)
		res = res * base % maxHashValue;

	return res;
}

std::set<size_t> FindSubStringNaive(const std::basic_string<char32_t>& text, const std::basic_string<char32_t>& sample)
{
	size_t textSize = text.size(), sampleSize = sample.size();
	std::set<size_t> enterIndicies;
	
	for (size_t textPosition = 0; textPosition <= textSize - sampleSize; ++textPosition)
	{
		for (size_t samplePosition = 0; samplePosition < sampleSize; ++samplePosition)
		{
			if (sample[samplePosition] != text[textPosition + samplePosition])
			{
				break;
			}
			else
			{
				if (samplePosition == sampleSize - 1)
					enterIndicies.insert(textPosition);
			}
		}
	}

	return enterIndicies;
}

int GetStringHash(const char* start, int size, int maxHashValue)
{
	int hash = 0;
	int alphabetSize = 256;

	for (int i = 0; i < size; ++i)
		hash = (hash * alphabetSize + start[i]) % maxHashValue;

	return hash;
}

bool AreStringsEqual(const char* text, const char* sample)
{
	for (; *sample != '\0'; ++sample, ++text)
		if (*sample != *text)
			return false;
	return true;
}

int RabinKarpSubStringSearch(const std::string& text, const std::string& sample)
{
	int textSize = text.size(), sampleSize = sample.size();
	int maxHashValue = 101;
	int alphabetSize = 256;
	int hashedLeaderWeight = PowHashed(alphabetSize, sampleSize - 1, maxHashValue);

	int sampleHash = GetStringHash(sample.c_str(), sampleSize, maxHashValue);
	int subTextHash = GetStringHash(text.c_str(), sampleSize, maxHashValue);

	for (int firstLeftIndex = 0; firstLeftIndex < textSize - sampleSize + 1; ++firstLeftIndex)
	{
		if (subTextHash == sampleHash && AreStringsEqual(text.c_str() + firstLeftIndex, sample.c_str()))
			return firstLeftIndex;
		
		subTextHash = subTextHash + maxHashValue - (unsigned int)text[firstLeftIndex] * hashedLeaderWeight % maxHashValue;
		subTextHash = (subTextHash * alphabetSize + text[(size_t)firstLeftIndex + sampleSize]);
		subTextHash %= maxHashValue;
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

std::set<size_t> Boyer_MooreSubstringSearch(const std::basic_string<char32_t>& text, const std::basic_string<char32_t>& sample)
{
	size_t sampleSize = sample.size();
	size_t textSize = text.size();

	std::set<size_t> enterIndicies;

	for (size_t textPosition = 0; textPosition <= textSize - sampleSize;)
	{
		for (size_t samplePosition = sampleSize - 1; samplePosition >= 0; --samplePosition)
		{
			if (sample[samplePosition] == text[textPosition + samplePosition])
			{
				if (samplePosition == 0)
				{
					enterIndicies.insert(textPosition);
					textPosition++;
					break;
				}
			}
			else
			{
				char32_t unmatched = text[textPosition + samplePosition];

				size_t shift;
				for (shift = 1; shift <= samplePosition; ++shift)
					if (unmatched == sample[samplePosition - shift])
						break;
				
				textPosition += shift;

				break;
			}
		}
	}

	return enterIndicies;
}