#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

// DP : Dynamic Programming(동적 계획법)
// 컴퓨터 공학의 Dynamic과는 관련이 없다.
// => 멋있어서 Dynamic 사용
// ==> 수학에서 최적화 기법으로 나온 알고리즘 패러다임

// 캐싱

// 부분 문제
// ex)  f(n) = f(n - 1) + f(n - 2)

// 참조 무결성 => 수학처럼 같은 값을 넣으면 항상 같은 값이 나와야 한다 ( 코딩은 외부 참조로 같은 값 넣어도 다른 값이 나올 수 있음)

// 피보나치 수열
// f(0) = 1
// f(1) = 1
// f(2) = 2
// f(3) = 3
// f(n) = f(n - 1) + f(n - 2)

int chache[100]; // 미리 계산한 값을 여기에 담아둠 => 계산값을 기억해 둬서 다시 계산 하지 않아도 됨 (기억해서 계산하기)

int Fibonacci(int n, int& count)
{
	// 기저사항 (더 쪼갤 수 없는 부분을 기저사항으로 저장)
	if (n == 0 || n == 1)
		return 1;

	if (n == 2)
		++count;
	
	// 메모이제이션, 캐싱
	if (chache[n] != -1)
		return chache[n];

	// 구하기
	return chache[n] = Fibonacci(n - 1, count) + Fibonacci(n - 2, count);
}

int chacheC[101][101];

int nCr(int n, int r)
{
	if (n < r || r < 0)
		return 0;

	if (n == 1 && r == 0)
		return 1;

	if (n == 1 && r == 1)
		return 1;

	if (chacheC[n][r] != -1)
		return chacheC[n][r];

	return chacheC[n][r] = nCr(n - 1, r - 1) + nCr(n - 1, r);
}

int DP_0()
{
	int count = 0;

	for (int i = 0; i < 100; i++)
	{
		chache[i] = -1;
	}

	for (int i = 0; i < 101; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			chacheC[i][j] = -1;
		}
	}

	cout << Fibonacci(70, count) << endl;

	__int64 start = GetTickCount64();

	cout << nCr(100, 10) << endl;

	__int64 end = GetTickCount64();

	cout << end - start << "ms" << endl;

	return 0;
}