#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

vector<vector<int>> adjacent2;
vector<bool> discovered;
vector<int> parent;
vector<int> best;

// MST
// minimum Spanning Tree (최소 신장 트리)
// 신장 트리
// => 최소 간선으로 모든 정점을 방문 할 수 있게 하는 간선들로 이루어진 트리
// 이 때
// 1. 정점이 n개일 때, 간선의 수는 n - 1이 된다.
// 2. 사이클리 존재하지 않는다.
// 
// 최소 신장 트리
// => 최소 간선 및 최소 가중치로 이루어진 신장트리

class DisjoinSet
{
public:
	DisjoinSet(int n)
	{
		_parent.resize(n, 0); // vector 초기화
		_rank.resize(n, 1);

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}
	~DisjoinSet() {}

	int FindLeader(int u)
	{
		if (u == _parent[u])
			return u;

		int parent = _parent[u];

		return FindLeader(parent);
	}

	void Merge(int u, int v)
	{
		int leaderU = FindLeader(u);
		int leaderV = FindLeader(v);

		if (leaderU == leaderV)
			return;

		if (_rank[leaderU] > _rank[leaderV])
		{
			std::swap(leaderU, leaderV);
		}

		_parent[leaderU] = leaderV;

		if (_rank[leaderU], _rank[leaderV])
		{
			_rank[leaderV]++;
		}
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

struct Edge
{
	int edgeU;
	int edgeV;
	int cost;
};

vector<Edge> edges;

void CreateGraphByMatrix()
{
    adjacent2 = vector<vector<int>>(7, vector<int>(7, -1));
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

    adjacent2[0][0] = 0;
    adjacent2[0][1] = 15;
    adjacent2[0][2] = 3;
    adjacent2[0][4] = 10;

    adjacent2[1][0] = 15;
    adjacent2[1][1] = 0;

    adjacent2[2][0] = 3;
    adjacent2[2][2] = 0;
    adjacent2[2][3] = 4;
    adjacent2[2][4] = 5;
    adjacent2[2][5] = 2;

    adjacent2[3][2] = 4;
    adjacent2[3][3] = 0;

    adjacent2[4][0] = 10;
    adjacent2[4][2] = 5;
    adjacent2[4][4] = 0;
    adjacent2[4][6] = 7;

    adjacent2[5][2] = 2;
    adjacent2[5][5] = 0;

    adjacent2[6][4] = 7;
    adjacent2[6][6] = 0;

	for (int u = 0; u < adjacent2.size(); u++)
	{
		for (int v = 0; v < adjacent2[u].size(); v++)
		{
			if (adjacent2[u][v] == -1 || u == v)
			{
				continue;
			}

			Edge edge;
			edge.edgeU = u;
			edge.edgeV = v;
			edge.cost = adjacent2[u][v];

			edges.push_back(edge);
		}
	}
}

vector<Edge> Kruskal(vector<Edge>& edges)
{
	vector<Edge> result;

	std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b)-> bool
	{
		return (a.cost < b.cost);
	});

	DisjoinSet sets(adjacent2.size());

	for (auto edge : edges)
	{
		if (sets.FindLeader(edge.edgeU) == sets.FindLeader(edge.edgeV))
			continue;

		result.push_back(edge);
		sets.Merge(edge.edgeU, edge.edgeV);
	}

	return result;
}

int main()
{
    CreateGraphByMatrix();

	auto result = Kruskal(edges);

    return 0;
}