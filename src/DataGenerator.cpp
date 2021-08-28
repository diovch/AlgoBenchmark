#include <random>
#include <string>

#include "DataGenerator.h"

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

template <typename dataType>
void CreateTree(tree<dataType>* parent, dataType* data, size_t size)
{
	tree<dataType>* current = parent;
	for (int i = 0; i < size; ++i)
	{
		InsertTreeElement(&current, data[i], parent);
	}
}

template <typename dataType>
void InsertTreeElement(tree<dataType>** l, dataType item, tree<dataType>* parent)
{
	//TODO finish method
}

std::string GenerateDNAString(size_t length)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<> distrib(1, 40);

	std::string result(length, ' ');

	for (int i = 0; i < length; ++i)
	{
		//Use `distrib` to transform the random unsigned int generated by gen into an int in [1, 12]
		if (distrib(gen) <= 10)
		{
			result[i] = 'a';
		}
		else if (distrib(gen) > 10 && distrib(gen) <= 20)
		{
			result[i] = 't';
		}
		else if (distrib(gen) > 20 && distrib(gen) <= 30)
		{
			result[i] = 'g';
		}
		else
		{
			result[i] = 'c';
		}
	}

	return result;
}