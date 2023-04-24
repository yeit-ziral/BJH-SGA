#pragma once
#include "../framework.h"

using namespace std;

struct User
{
	int guild_id;
};

void GuildSystem()
{
	vector<User> users;

	for (int i = 0; i < 1000; i++)
	{
		User user;
		user.guild_id = i;

		users.push_back(user);
	}

	// �ε��� 1�� ������ �ε��� 5�� ������ ��� ��ħ
	users[1].guild_id = users[5].guild_id;
	// [0] [1] [2] [3] [4] [5]
	//  0   5   2   3   4   5
}

class NaiveDJ
{
public:
	NaiveDJ(int n)
	{
		_parent.resize(n, 0); // vector �ʱ�ȭ

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}
	~NaiveDJ() {}

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

		_parent[leaderV] = _parent[leaderV];
	}

private:
	vector<int> _parent;
};

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