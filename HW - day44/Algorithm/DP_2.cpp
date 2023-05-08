#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

// LIS (longest Increasing Sequence)
// 부분 증가 수열에서 제일 긴 수열 길이를 찾는다.
// Seq : 1 2 9 5 8 10

// 부분 수열 : 순서는 유지하되, 인접하지 않을 수 도 있다
// 1 2 5
// 1 2 9 8
// 2 9 1 -> 아님(순서 유지 x)

// 부분 증가 수열 : 부분 수열이면서 점점 증가되는 순서로 유지되는 수열
// 1 2 5
// 1 2 9 8 -> 아님(9 > 8)

//vector<int> seq =  {0, 5, 1, 2, 3, 1 };
//vector<int> seq =  {3, 5, 1, 2, 4, 1 }; { 1, 2, 3, 4, 3, 5, 6 }
//vector<int> seq = { 5, 6, 7, 8, 1, 2, 3 };
vector<int> seq = { 1, 2, 3, 4, 3, 4, 5, 6 };

// LIS(5) : 1 => {1}
// LIS(4) : 1 => {3} or {1} -> LIS(5) or LIS(5) + 1
// LIS(3) : 2 => {2, 3} -> LIS(4) or LIS(4) + 1
// LIS(2) : 3 => {1, 2, 3} -> LIS(3) or LIS(3) + 1
// LIS(1) : 3 => {1, 2, 3} -> LIS(2) or LIS(2) + 1
// LIS(0) : 4 => {0, 1, 2, 3} -> LIS(1) or LIS(1) + 1

vector<int>ca = vector<int>(100, -1);

int len = seq.size() - 1;

int a;

int b = 0;

vector<int> A;

int LIS_mine(int pos)
{
	if (pos == len)
	{
		A.push_back(pos);
		return 1;
	}

	if (ca[pos] != -1)
		return ca[pos];

	a = A.size();

	if (seq[pos] > seq[pos + 1])
	{
		A.clear();
		A.push_back(seq[pos]);
		ca[pos] = LIS_mine(pos + 1);
	}
	else
	{
		A.push_back(seq[pos]);
		ca[pos] = LIS_mine(pos + 1) + 1;
	}

	if (a > b)
	{
		b = a;

		ca[pos] = a;
	}
	else
	{
		ca[pos] = b;
	}

	for (int i = pos - 1; i > 0; i--)
	{
		LIS_mine(i);
	}


	return ca[pos];
}

int LIS(int pos)
{
	// 기저
	if (pos == len)
		return 1;

	// 캐싱
	int& ref = ca[pos];

	// 구하기
	//ref = 1; // ref = -1이라서 발생하는 에러 예방
	for (int next = pos + 1; next < seq.size(); next++)
	{
		if (seq[pos] <= seq[next])
		{
			ref = max(ref, LIS(next) + 1);
		}
	}

	return ref;
}

int myLis(int pos)
{
	if (pos == len)
		return 1;

	int& ref = ca[pos];

	/*if (ref != -1)
		return ref;*/

	int maxLis = 0;

	int index = pos + 1;

	for (int i = pos + 1; i < seq.size(); i++)
	{
		if (maxLis <= myLis(i))
		{
			if (seq[i] <= seq[index])
			{
				index = i;
			}

			maxLis = myLis(i);
		}
	}

	if (seq[pos] < seq[index] || (index - pos) > maxLis)
		ref = maxLis + 1;
	else
		ref = maxLis;
}

int main()
{
	int lis = 0;

	// 정석
	for (int i = 0; i < seq.size(); i++)
	{
		lis = max(lis, LIS(i));
	}

	cout << lis << endl;

	// 교수님 방식
	lis = myLis(0);

	cout << lis << endl;

	return 0;
}