#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

// DP : Dynamic Programming(���� ��ȹ��)
// ��ǻ�� ������ Dynamic���� ������ ����.
// => ���־ Dynamic ���
// ==> ���п��� ����ȭ ������� ���� �˰��� �з�����

// ĳ��

// �κ� ����
// ex)  f(n) = f(n - 1) + f(n - 2)

// ���� ���Ἲ => ����ó�� ���� ���� ������ �׻� ���� ���� ���;� �Ѵ� ( �ڵ��� �ܺ� ������ ���� �� �־ �ٸ� ���� ���� �� ����)

// �Ǻ���ġ ����
// f(0) = 1
// f(1) = 1
// f(2) = 2
// f(3) = 3
// f(n) = f(n - 1) + f(n - 2)

int chache[100]; // �̸� ����� ���� ���⿡ ��Ƶ� => ��갪�� ����� �ּ� �ٽ� ��� ���� �ʾƵ� �� (����ؼ� ����ϱ�)

int Fibonacci(int n, int& count)
{
	// �������� (�� �ɰ� �� ���� �κ��� ������������ ����)
	if (n == 0 || n == 1)
		return 1;

	if (n == 2)
		++count;
	
	// �޸������̼�, ĳ��
	if (chache[n] != -1)
		return chache[n];

	// ���ϱ�
	return chache[n] = Fibonacci(n - 1, count) + Fibonacci(n - 2, count);
}

int Fchache[100];

int Factorial(int n)
{
	if (n == 0 || n == 1)
		return 1;

	if (Fchache[n] != -1)
		return chache[n];

	return Fchache[n] = Factorial(n - 1) * n;
}

int nCr(int n, int r)
{
	if (n >= r)
	{
		return Factorial(n) / (Factorial(r) * Factorial(n - r));
	}
	else
		return -1;
}

int main()
{
	int count = 0;

	for (int i = 0; i < 100; i++)
	{
		chache[i] = -1;
	}

	for (int i = 0; i < 100; i++)
	{
		Fchache[i] = -1;
	}

	__int64 start = GetTickCount64();

	cout << Fibonacci(70, count) << endl;

	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;

	cout << Factorial(100) << endl;

	cout << nCr(100, 10) << endl;

	return 0;
}