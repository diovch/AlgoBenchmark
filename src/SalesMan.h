#pragma once

#include <vector>


void rec(std::vector<std::vector<float>>& cityDistances, std::vector<int>& cityIndicies, std::vector<bool>& used, 
	float& minDistance, int idx, int cityNumber, float len, size_t& routeCount)
{
	if (len >= minDistance) // ���������
		return;

	if (idx == cityNumber) // ����� �� �������� ������� � ������������
	{
		routeCount++;
		minDistance = std::min(minDistance, len + cityDistances[cityIndicies[idx - 1]][0]); // len = ���� �� ��������: 0, 1, ..., n-1. a[p[idx - 1]][0] = ���� �� n-1 � 0 �����

		return;
	}

	for (int i = 1; i <= cityNumber - 1; i++)
	{
		if (used[i]) // ������ �� ����������
			continue;

		cityIndicies[idx] = i;
		used[i] = true;

		used[i] = false;
	}
}

