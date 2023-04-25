#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class DisjoinSet
{
public:
	DisjoinSet(int n)
	{
		_parent.resize(n, 0); // vector �ʱ�ȭ
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

		if (_rank[leaderU] == _rank[leaderV])
		{
			_rank[leaderV]++;
		}
	}

private:
	vector<int> _parent;
	vector<int> _rank;
};

struct Roads
{
	int u;
	int v;

	int cost;
};

int solution(int n, vector<vector<int>> costs) {
	int answer = 0;
	// costs[n][0],costs[n][1] => ����� �� ��
	// costs[n][2] => �� �� ������ ����ġ

	vector<Roads> roads;

	for (int i = 0; i < n; i++)
	{
		// ������ �ִ� ���� Roads�� ����
		if (i < n)
		{
			Roads road;
			road.cost = costs[i][2];
			road.u = costs[i][0];
			road.v = costs[i][1];
			roads.push_back(road);
		}
	}

	DisjoinSet sets(n);

	for (auto road : roads)
	{
		int u = road.u;
		int v = road.v;

		if (sets.FindLeader(u) == sets.FindLeader(v))
			continue;

		sets.Merge(u, v);
		answer++;
	}

	//priority_queue<int> pq;

	//for(auto iter : costs)
	//{
	//    pq.push(iter[2]);
	//}

	return answer;
}

int main()
{
	vector<vector<int>> costs = { {0, 1, 1},{0, 2, 2},{1, 2, 5},{1, 3, 1},{2, 3, 8} };

	cout << solution(4, costs) << endl;

	return 0;
}