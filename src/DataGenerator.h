#pragma once
#include <string>

struct list
{
	int data;
	struct list* next = NULL;
};

std::string GenerateString(size_t length);