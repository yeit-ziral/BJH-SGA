#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// 과제 머지솔트 조사

// QuickSort
// 값이 같을 경우 같은 값의 데이터의 순서가 바뀔수 있다 => 불완전 정렬

int Partition(vector<int>& v, int left, int right)
{
	int pivot = v[left];
	int lowIndex = left + 1;
	int highIndex = right;

	while (true)
	{
		if (lowIndex > highIndex)
			break;

		while (lowIndex <= right && pivot >= v[lowIndex])
		{
			lowIndex++;
		}

		while (highIndex >= left + 1 && pivot <= v[highIndex])
		{
			highIndex--;
		}

		if (lowIndex < highIndex)
			std::swap(v[highIndex], v[lowIndex]);
	}

	std::swap(v[highIndex], v[left]);

	return highIndex;
}

void QuickSort(vector<int>& v, int left, int right)
{
	if (left >= right)
		return;

	int pivotIndex = Partition(v, left, right);

	cout << left << " ~ " << pivotIndex - 1 << endl;
	QuickSort(v, left, pivotIndex - 1);
	QuickSort(v, pivotIndex + 1, right);
}

int QuickSort()
{
	vector<int> v = { 55, 30, 15, 100, 1, 5, 70, 40 };

	QuickSort(v, 0, 7);

	return 0;
}