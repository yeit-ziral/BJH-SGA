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
vector<int> seq =  {3, 5, 1, 2, 4, 1 };

// LIS(5) : 1 => {1}
// LIS(4) : 1 => {3} or {1} -> LIS(5) or LIS(5) + 1
// LIS(3) : 2 => {2, 3} -> LIS(4) or LIS(4) + 1
// LIS(2) : 3 => {1, 2, 3} -> LIS(3) or LIS(3) + 1
// LIS(1) : 3 => {1, 2, 3} -> LIS(2) or LIS(2) + 1
// LIS(0) : 4 => {0, 1, 2, 3} -> LIS(1) or LIS(1) + 1

vector<int>ca = vector<int>(100, -1);

int len = seq.size() - 1;

int a;

int LIS(int pos)
{
	if (pos == len)
		return 1;

	if (ca[pos] != -1)
		return ca[pos];

	int b = seq[pos];

	if (a > b)
	{
		a = a;
	}
	else
	{
		a = b;
	}

	if (seq[pos] > seq[pos + 1])
		ca[pos] = LIS(pos + 1);
	else
		ca[pos] = LIS(pos + 1) + 1;


	return ca[pos];
}

int main()
{
	cout << LIS(1) << endl; // 4 나와야 됨

	return 0;
}