#pragma once

#include <vector>

//std::vector<std::vector<float>> a;
//std::vector<int> p;
//std::vector<bool> used;
//int ans = INT_MAX;

void rec(std::vector<std::vector<float>>& cityDistances, std::vector<int>& cityIndicies, std::vector<bool>& used, 
	float& minDistance, int idx, int cityNumber, float len, size_t& routeCount)
{
	if (len >= minDistance) // ���������
		return;

	if (idx == cityNumber) // ����� �� �������� ������� � ������������
	{
		routeCount++;
		minDistance = std::min(minDistance, len + cityDistances[cityIndicies[idx - 1]][0]); // len = ���� �� ��������: 0, 1, ..., n-1. a[p[idx - 1]][0] = ���� �� n-1 � 0 �����
		
		//for (auto& v : cityIndicies)
		//	std::cout << v << " ";
		//std::cout << std::endl;

		return;
	}

	for (int i = 1; i <= cityNumber - 1; i++)
	{
		if (used[i]) // ������ �� ����������
			continue;

		cityIndicies[idx] = i;
		used[i] = true;

		//if (cityDistances[cityIndicies[idx - 1]][cityIndicies[idx]] < 0.)
		//	continue;
		//else
			rec(cityDistances, cityIndicies, used, minDistance, idx + 1, cityNumber, len + cityDistances[cityIndicies[idx - 1]][cityIndicies[idx]], routeCount); // ����������� �����

		used[i] = false;
	}
}

