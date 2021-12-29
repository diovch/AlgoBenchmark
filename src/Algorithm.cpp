#include <iostream>
#include <math.h>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>

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

unsigned int GetStringHash(const char* start, int size, int maxHashValue)
{
	unsigned int hash = 0;
	int alphabetSize = 256;

	for (int i = 0; i < size; ++i)
		hash = (hash * alphabetSize + start[i]) % maxHashValue;

	return hash;
}

unsigned int GetStringHash(const wchar_t* start, unsigned int size, unsigned int maxHashValue)
{
	unsigned int hash = 0;
	unsigned int alphabetSize = (int)1 << (8 * sizeof(wchar_t));

	for (int i = 0; i < size; ++i)
		hash = (hash * alphabetSize + (unsigned int)start[i]) % maxHashValue;

	return hash;
}

unsigned long
DanBernsteinHash(unsigned char* str)//Dan Bernstein
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

int GetNaiveStringHash(std::string& str)
{
	int hash = 0;
	int alphabetSize = 256;

	for (const auto& sym : str)
		//hash += (hash * alphabetSize + sym);
		hash += (int)sym;

	return hash;
}

std::string GenerateRandomString(int size)
{
	std::string res(size, '\0');

	for (auto& sym : res)
		sym = (unsigned char)GenerateIntNum(1, 127);

	return res;
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

	std::vector<size_t> offset(256, sampleSize);
	for (size_t i = 0; i < sampleSize - 1; ++i)
		offset[sample[i] % 256] = sampleSize - i - 1;

	std::set<size_t> enterIndicies;
	size_t similarityNumber = 0;

	for (size_t textPosition = 0; textPosition <= textSize - sampleSize;)
	{
		for (size_t samplePosition = sampleSize - 1; samplePosition >= 0; --samplePosition)
		{
			if (sample[samplePosition] == text[textPosition + samplePosition])
			{
				similarityNumber++;
				if (similarityNumber == sampleSize)
				{
					enterIndicies.insert(textPosition);
					textPosition++;
					similarityNumber = 0;
					break;
				}
			}
			else
			{
				size_t shift = 1;
				char32_t unmatched = text[textPosition + samplePosition];
				shift = offset[unmatched % 256] - similarityNumber;
				textPosition += shift;
				similarityNumber = 0;
				break;
			}
		}
	}
	return enterIndicies;
}

void swap(int* a, int* b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}

void InsertionSort(std::vector<int>& dataArray)
{
	for (size_t keyIndex = 1; keyIndex < dataArray.size(); ++keyIndex)
	{
		int key = dataArray[keyIndex];
		int swapIndex = keyIndex - 1;

		while (swapIndex >= 0 && key < dataArray[swapIndex])
		{
			dataArray[swapIndex + 1] = dataArray[swapIndex];
			swapIndex--;
		}
		dataArray[swapIndex + 1] = key;
	}
}



std::vector<int> GetBublePassedVector(std::vector<int>& v, enum ComparisonType compType)
{
	auto vectorSize = v.size();
	if (vectorSize % 2 != 0)
		std::cout << "Vector is meant to have even size";


	std::vector<int> bubbledCopy(v.begin(), v.end());

	if (compType == ComparisonType::MIN)
	{
		for (size_t i = 1; i < vectorSize; i++)
			if (bubbledCopy[i] < bubbledCopy[i - 1])
				swap(&bubbledCopy[i], &bubbledCopy[i - 1]);
	}
	else
	{
		for (size_t i = 1; i < vectorSize; i++)
			if (bubbledCopy[i] > bubbledCopy[i - 1])
				swap(&bubbledCopy[i], &bubbledCopy[i - 1]);
	}
		
	
	return bubbledCopy;
}

size_t GetParent(size_t i) { return i / 2; }
size_t GetLeft(size_t i) { return 2 * i + 1; }
size_t GetRight(size_t i) { return 2 * i + 2; }

//(int arr[], int n, int i)
void Heapify(std::vector<int>& dataArray, size_t heapSize, size_t i)
{
	int largest = i;
	// Инициализируем наибольший элемент как корень
	int left = 2 * i + 1; // левый = 2*i + 1
	int right = 2 * i + 2; // правый = 2*i + 2

 // Если левый дочерний элемент больше корня
	if (left < heapSize && dataArray[left] > dataArray[largest])
		largest = left;

	// Если правый дочерний элемент больше, чем самый большой элемент на данный момент
	if (right < heapSize && dataArray[right] > dataArray[largest])
		largest = right;

	// Если самый большой элемент не корень
	if (largest != i)
	{
		swap(&dataArray[i], &dataArray[largest]);

		// Рекурсивно преобразуем в двоичную кучу затронутое поддерево
		Heapify(dataArray, heapSize, largest);
	}
}
// (int arr[], int n)
void HeapSort(std::vector<int>& dataArray)
{
	size_t n = dataArray.size();
	// Построение кучи (перегруппируем массив)
	for (int i = n / 2 - 1; i >= 0; i--) // начинаем с предпоследнего уровня
		Heapify(dataArray, n, i);

	// Один за другим извлекаем элементы из кучи
	for (int i = n - 1; i >= 0; i--)
	{
		// Перемещаем текущий корень в конец
		swap(&dataArray[0], &dataArray[i]);

		// вызываем процедуру heapify на уменьшенной куче
		Heapify(dataArray, i, 0); // i здесь - размер кучи, 0 - корень
	}
}

void mergesort(std::vector<int>& data, int l, int r)
{
	if (r <= l) return;

	int m = (r + l) / 2;
	mergesort(data, l, m);
	mergesort(data, m + 1, r);

	merge(data, l, m, r);
}

void merge(std::vector<int>& data, int left, int separator, int right)
{
	std::vector<int> temp(data.size());
	
	int i, j;
	for (i = separator + 1; i > left; i--) // копирование левой части
		temp[i - 1] = data[i - 1];
	
	for (j = separator; j < right; j++) 
		temp[right + separator - j] = data[j + 1]; // копирование правой части

	for (int k = left; k <= right; k++) // слияние
		if (temp[j] < temp[i])
		{
			data[k] = temp[j];
			j--;
		}
		else
		{
			data[k] = temp[i];
			i++;
		}
}



void perm(std::vector<int>& cityIndicies, std::vector<std::vector<float>>& cityDistances,  int lf, float* minDistance, size_t* count)
{
	if (lf >= cityIndicies.size()) 
	{                           // перестановки окончены
		//print(cityIndicies, cityDistances);                // выводим перестановку
		float currentDistance = dist(cityIndicies, cityDistances);
		
		//if (currentDistance <= *minDistance) 
		{
			(*count)++;
			*minDistance = currentDistance;
		}
		return;
	}

	perm(cityIndicies, cityDistances, lf + 1, minDistance, count); // перестановки элементов справа от lf
	for (size_t i = lf + 1; i < cityIndicies.size(); i++) 
	{           // теперь каждый элемент ar[i], i > lf
		swap(cityIndicies, lf, i);                            // меняем местами с ar[lf]
		perm(cityIndicies, cityDistances, lf + 1, minDistance, count);  // и снова переставляем всё справа
		swap(cityIndicies, lf, i);                            // возвращаем элемент ar[i] назад
	}
}

float dist(std::vector<int>& cityIndicies, std::vector<std::vector<float>>& cityDistances)
{
	// расстояние между первым и последним городом
	float distance = cityDistances[cityIndicies[0] - 1][cityIndicies[cityIndicies.size() - 1] - 1]; 

	for (int i = 0; i < cityIndicies.size() - 1; i++)
	{
		int firstCity = cityIndicies[i] - 1;
		int secondCity = cityIndicies[i + 1] - 1;
		distance += cityDistances[firstCity][secondCity];
	}
		
	return distance;
}

void print(std::vector<int>& cityIndicies, std::vector<std::vector<float>>& cityDistances)
{
	std::cout << "Cities route ";
	
	for (auto& v : cityIndicies)
		std::cout << v << " ";
	
	std::cout << std::endl << "Distance of the route ";
	std::cout << dist(cityIndicies, cityDistances) << std::endl;
}

void swap(std::vector<int>& ar, int i, int j)
{
	int temp = ar[i];
	ar[i] = ar[j];
	ar[j] = temp;
}

void QuickSort(std::vector<int>& array, int low, int high)
{
	int i = low;
	int j = high;
	int pivot = array[(i + j) / 2];
	int temp;

	while (i <= j)
	{
		while (array[i] < pivot)
			i++;
		while (array[j] > pivot)
			j--;
		if (i <= j)
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
			i++;
			j--;
		}
	}
	if (j > low)
		QuickSort(array, low, j);
	if (i < high)
		QuickSort(array, i, high);
}

void MultiPhaseSort(std::vector<int>& ar)
{
	size_t numberOfBlocks = 10;
	size_t numberOfBlockElements = ar.size() / numberOfBlocks;
	

	for (size_t i = 0; 
		i <= ar.size() - 2; 
		i += numberOfBlockElements)
	{
		size_t j = (ar.size() - i > numberOfBlockElements) ? (i + numberOfBlockElements - 1) : (ar.size() - 1);
		QuickSort(ar, i, j);
	}

	size_t left = 0;
	size_t separator = left + numberOfBlockElements - 1;
	//size_t right = (ar.size() - separator > numberOfBlockElements) ? (separator + numberOfBlockElements) : (ar.size() - 1);

	while (separator <= ar.size() - 2)
	{
		size_t right = (ar.size() - separator > numberOfBlockElements) ? (separator + numberOfBlockElements) : (ar.size() - 1);
		merge(ar, left, separator, right);

		separator += numberOfBlockElements;
	}
}

void DFS(int cityIndex, std::vector<std::vector<bool>>& isRoadExists, std::vector<bool>& isVisited)
{
	isVisited[cityIndex] = true;

	for (int neighborIndex = 0; neighborIndex < isRoadExists[cityIndex].size(); neighborIndex++)
	{
		bool isNeighbor = isRoadExists[cityIndex][neighborIndex];

		if (!isNeighbor || isVisited[neighborIndex] || neighborIndex == cityIndex)
			continue;
		
		DFS(neighborIndex, isRoadExists, isVisited);
	}
}

bool IsOneComponent(std::vector<std::vector<bool>>& isRoadExists)
{
	std::vector<bool> isVisited(isRoadExists[0].size(), false);

	DFS(0, isRoadExists, isVisited); // если компонента одна то мы посетим все вершины за один проход

	if (isVisited == std::vector<bool>(isVisited.size(), true))
		return true;
	else
		return false;

	//for (int i = 0; i < isVisited.size(); i++)
	//{
	//	if (!isVisited[i])
	//		DFS(i, isRoadExists, isVisited);
	//}
}

int GetNumberOfConnections(std::vector<std::vector<bool>>& isRoadExists)
{
	int res = 0;
	for (int i = 0; i < isRoadExists.size(); i++)
		for (int j = 0; j < i; j++)
			if (isRoadExists[i][j])
				res++;

	return res;
}

float GetMinDistance(std::vector<std::vector<float>>& cityDistances, std::vector<std::vector<bool>>& isRoadExists, int& count)
{
	float minDistance = FLT_MAX;

	std::vector<int> cityIndicies(isRoadExists.size());
	for (int i = 0; i < cityIndicies.size(); i++) 
		cityIndicies[i] = i;

	do
	{
		//if (!isRoadExists[cityIndicies[0]][*(cityIndicies.end() - 1)])
		//	continue;

		float temp = 0.;
		//float temp = cityDistances[cityIndicies[0]][*(cityIndicies.end() - 1)];

		for (auto cityIndexIt = cityIndicies.begin(); cityIndexIt != (cityIndicies.end() - 1); cityIndexIt++)
		{
			count++;
			if (!isRoadExists[*cityIndexIt][*(cityIndexIt + 1)])
			{
				temp = -1.;
				break;
			}
			else
				temp += cityDistances[*cityIndexIt][*(cityIndexIt + 1)];
		}

		if (temp < 0.)
			continue;
		if (temp < minDistance)
			minDistance = temp;
	} 
	while (std::next_permutation(cityIndicies.begin(), cityIndicies.end()));

	return minDistance;
}