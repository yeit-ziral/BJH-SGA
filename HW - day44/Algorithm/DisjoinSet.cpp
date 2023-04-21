#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

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

class DisJoinSet
{
public:
	DisJoinSet(int n)
	{
		_parent.resize(n, 0); // vector �ʱ�ȭ

		for (int i = 0; i < n; i++)
		{
			_parent[i] = i;
		}
	}
	~DisJoinSet() {}

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

int mainx()
{
	DisJoinSet guild = DisJoinSet(10);

	cout << guild.FindLeader(5) << endl;

	guild.Merge(1, 5);
	guild.Merge(5, 2);
	guild.Merge(5, 9);
	guild.Merge(5, 3);

	cout << guild.FindLeader(3) << endl;

	return 0;
}