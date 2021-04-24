#include "Algorithm.h"

bool FindSubStringNaive(const std::string text, const std::string subString)
{
	int sameCharacterCounter = 0;
	for (int enterPosition = 0; enterPosition < text.size() - subString.size() - 1; ++enterPosition)
	{
		if (text[enterPosition] == subString[0])
		{
			for (int j = enterPosition++; j < subString.size(); ++j)
			{
				if (text[j] != subString[j])
				{
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