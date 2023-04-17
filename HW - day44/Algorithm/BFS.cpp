#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// 이산수학의 그래프
// 그래프에 대한 조사
// 그래프의 기원
// 그래프를 쓰는 이유

vector<vector<bool>> adjacent2;
vector<bool> discovered;
vector<int> parent;

void CreateGraphByMatrix()
{
    adjacent2 = vector<vector<bool>>(7, vector<bool>(7, false));
    discovered = vector<bool>(7, false);
    parent = vector<int>(7, -1);

    //    0  1  2  3  4  5  6
    // 0  T  T  T  F  T  F  F
    // 1  T  T  F  F  F  F  F
    // 2  T  F  T  T  F  T  F
    // 3  F  F  T  T  F  F  F
    // 4  T  F  F  F  T  F  T
    // 5  F  F  T  F  F  T  F
    // 6  F  F  F  F  T  F  F

    adjacent2[0][0] = true;
    adjacent2[0][1] = true;
    adjacent2[0][2] = true;
    adjacent2[0][4] = true;

    adjacent2[1][0] = true;
    adjacent2[1][1] = true;

    adjacent2[2][0] = true;
    adjacent2[2][2] = true;
    adjacent2[2][3] = true;
    adjacent2[2][5] = true;

    adjacent2[3][2] = true;
    adjacent2[3][3] = true;

    adjacent2[4][0] = true;
    adjacent2[4][4] = true;
    adjacent2[4][6] = true;

    adjacent2[5][2] = true;
    adjacent2[5][5] = true;

    adjacent2[6][4] = true;
    adjacent2[6][6] = true;
}

void BFS(int start)
{
    queue<int> queue;
    parent[start] = start;

    queue.push(start);

    while (true)
    {
        if (queue.empty() == true)
            break;

        int here = queue.front();
        queue.pop();

        for (int there = 0; there < 7; there++)
        {
            if (adjacent2[here][there] == false)
                continue;

            if (discovered[there])
                continue;

            queue.push(there);
            parent[there] = here;
            discovered[there] = true;
            cout << there << "방문!!" << endl;
        }
    }
}

//int BfsAll()
//{
//    int count = 0;
//
//    for (int start = 0; start < 7; start++)
//    {
//        if (discovered[start] == false)
//        {
//            BFS(start);
//            count++;
//        }
//    }
//
//    return count;
//}

int main()
{
    CreateGraphByMatrix();

    BFS(0);

    int targetNode = 3;

    while (true)
    {
        cout << targetNode << "의 부모 : " << parent[targetNode] << endl;

        if (parent[targetNode] == targetNode)
            break;

        targetNode = parent[targetNode];
    }

    return 0;
}