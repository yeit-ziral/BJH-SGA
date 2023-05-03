#include <string>
#include <vector>
#include <iostream>
#include <windows.h>

using namespace std;

// ENCHANT

// 강화를 하는데
// + 1
// + 2
// + 3

// 8강을 하고 싶다... 이때 강화하는 대로 나오는 모든 경우의 수
// 3강을 하고 싶다
// 1 1 1
// 2 1
// 1 2
// 3

// 0강 f(0) 
// 1

// 1강 f(1)
// 1

// 2강 f(2)
// 2

// 3강 f(3) = 4
// 1 1 1
// 1 2
// 2 1
// 3

// 4강 f(4) = f(3) f(2) 
// 1 1 1 1
// 1 2 1
// 1 1 2
// 2 1 1
// 1 3
// 3 1


// f(N) = f(N - 1) + f(N - 2) + f(N - 3)

vector<int> cache = vector<int>(100, -1);
int Num = 3;

//int Enchant(int N)
//{
//	// 예외사항
//	if (N > Num)
//		return 0;
//	if (N == Num)
//		return 1;
//
//	//캐쉬
//	int& ref = cache[N];
//	if (ref != -1)
//		return ref;
//
//	// 구하기
//	ref = Enchant(N + 1) + Enchant(N + 2) + Enchant(N + 3);
//
//	return ref;
//}

int Enchant(int N)
{
    // 기저 사항
    if (N == 0 || N == 1)
        return 1;
    if (N == 2)
        return 2;

    if (cache[N] != -1)
        return cache[N];

    cache[N] = Enchant(N - 1) + Enchant(N - 2) + Enchant(N - 3);

    return cache[N];
}

int DP_1()
{
	cout << Enchant(5) << endl;

	return 0;
}