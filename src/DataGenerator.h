#pragma once
#include <string>

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