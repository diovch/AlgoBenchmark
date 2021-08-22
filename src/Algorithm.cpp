#include <iostream>

#include "Algorithm.h"

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
				if (text[enterPosition + j] != subString[j])
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

list* SearchInList(list* first, int target)
{
	if (first == NULL)
		return NULL;

	if (first->data == target)
		return first;
	else
		return SearchInList(first->next, target);
}

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
		FindPreviousElement(previous->next, target);
	}
}