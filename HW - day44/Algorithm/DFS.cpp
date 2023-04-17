#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

// �̻������ �׷���
// �׷����� ���� ����
// �׷����� ���
// �׷����� ���� ����

vector<vector<bool>> adjacent2;
vector<bool> discovered;

void CreateGraphByMatrix()
{
    adjacent2 = vector<vector<bool>>(7, vector<bool>(7, false));
    discovered = vector<bool>(7, false);

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

void DFS(int start)
{
    if (discovered[start])
        return;
    discovered[start] = true;
    cout << start << "�� �湮�߽��ϴ�." << endl;

    for (int there = 0; there < adjacent2.size(); there++)
    {
        // ������ ������� �����ϸ� ��������
        if (start == there)
            continue;

        // �������ִ°�?
        if (adjacent2[start][there] == false)
            continue;

        // �湮����
        if (discovered[there] == true)
            continue;

        // ������ ã�����
        DFS(there);
    }
}

int DfsAll()
{
    int count = 0;

    for (int start = 0; start < 7; start++)
    {
        if (discovered[start] == false)
        {
            DFS(start);
            count++;
        }
    }

    return count;
}

int DFS()
{
    CreateGraphByMatrix();
    DFS(0);
    int count = DfsAll();
    return 0;
}