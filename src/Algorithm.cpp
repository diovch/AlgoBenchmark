#include <iostream>
#include <math.h>
#include <set>
#include <map>
#include <vector>
#include <unordered_map>

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

void merge(std::vector<int>& data, int l, int m, int r)
{
	std::vector<int> temp(data.size());

	int i, j;
	for (i = m + 1; i > l; i--) temp[i - 1] = data[i - 1];
	for (j = m; j < r; j++) temp[r + m - j] = data[j + 1];

	for (int k = l; k <= r; k++)
		if (temp[j] < temp[i])
			data[k] = temp[j--];
		else
			data[k] = temp[i++];
}

void perm(std::vector<int>& ar, std::vector<std::vector<float>>& dists,  int lf)
{
	if (lf >= ar.size()) 
	{                           // перестановки окончены
		print(ar, dists);                // выводим перестановку
		return;
	}

	perm(ar, dists, lf + 1);                                // перестановки элементов справа от lf
	for (size_t i = lf + 1; i < ar.size(); i++) 
	{           // теперь каждый элемент ar[i], i > lf
		swap(ar, lf, i);                            // меняем местами с ar[lf]
		perm(ar, dists, lf + 1);                            // и снова переставляем всё справа
		swap(ar, lf, i);                            // возвращаем элемент ar[i] назад
	}
}

float dist(std::vector<int>& ar, std::vector<std::vector<float>>& dists)
{
	float distance = 0.;
	for (int i = 0; i < ar.size() - 1; i++)
		distance += dists[ar[i]][ar[i + 1]];
	return distance;
}

void print(std::vector<int>& ar, std::vector<std::vector<float>>& dists)
{
	for (auto& v : ar)
		std::cout << v << " ";
	std::cout << std::endl << dist(ar, dists);
}

void swap(std::vector<int>& ar, int i, int j)
{
	int temp = ar[i];
	ar[i] = ar[j];
	ar[j] = temp;
}