#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

// LIS (longest Increasing Sequence)
// �κ� ���� �������� ���� �� ���� ���̸� ã�´�.
// Seq : 1 2 9 5 8 10

// �κ� ���� : ������ �����ϵ�, �������� ���� �� �� �ִ�
// 1 2 5
// 1 2 9 8
// 2 9 1 -> �ƴ�(���� ���� x)

// �κ� ���� ���� : �κ� �����̸鼭 ���� �����Ǵ� ������ �����Ǵ� ����
// 1 2 5
// 1 2 9 8 -> �ƴ�(9 > 8)

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
	cout << LIS(1) << endl; // 4 ���;� ��

	return 0;
}