//#include <iostream>
//#include <string>
//#include <vector>
//#include <algorithm>
//
//using namespace std;
//
//class DisjoinSet
//{
//public:
//	DisjoinSet(int n)
//	{
//		_parent.resize(n, 0); // vector 초기화
//		_rank.resize(n, 1);
//
//		for (int i = 0; i < n; i++)
//		{
//			_parent[i] = i;
//		}
//	}
//	~DisjoinSet() {}
//
//	int FindLeader(int u)
//	{
//		if (u == _parent[u])
//			return u;
//
//		int parent = _parent[u];
//
//		return FindLeader(parent);
//	}
//
//	void Merge(int u, int v)
//	{
//		int leaderU = FindLeader(u);
//		int leaderV = FindLeader(v);
//
//		if (leaderU == leaderV)
//			return;
//
//		if (_rank[leaderU] > _rank[leaderV])
//		{
//			std::swap(leaderU, leaderV);
//		}
//
//		_parent[leaderU] = leaderV;
//
//		if (_rank[leaderU] == _rank[leaderV])
//		{
//			_rank[leaderV]++;
//		}
//	}
//
//private:
//	vector<int> _parent;
//	vector<int> _rank;
//};
//
//struct Roads
//{
//	int u;
//	int v;
//
//	int cost;
//};
//
//int solution(int n, vector<vector<int>> costs) {
//	int answer = 0;
//	// costs[n][0],costs[n][1] => 연결될 두 점
//	// costs[n][2] => 두 점 사이의 가중치
//
//	vector<Roads> roads;
//
//	for (int i = 0; i < n; i++)
//	{
//		// 섬들을 있는 정보 Roads에 저장
//		if (i < n)
//		{
//			Roads road;
//			road.cost = costs[i][2];
//			road.u = costs[i][0];
//			road.v = costs[i][1];
//			roads.push_back(road);
//		}
//	}
//
//	DisjoinSet sets(n);
//
//	for (auto road : roads)
//	{
//		int u = road.u;
//		int v = road.v;
//
//		if (sets.FindLeader(u) == sets.FindLeader(v))
//			continue;
//
//		sets.Merge(u, v);
//		answer += road.cost;
//	}
//
//	//priority_queue<int> pq;
//
//	//for(auto iter : costs)
//	//{
//	//    pq.push(iter[2]);
//	//}
//
//	return answer;
//}

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <string>

using namespace std;

//void Sapperate(string letter, vector<string> Letter)
//{
//	map<int, string> A;
//
//	while (true)
//	{
//		string a;
//
//		string s;
//
//		for (int i = 0; i < letter.size(); i++)
//		{
//			
//
//			if (s == " ")
//				break;
//
//			a += s;
//		}
//
//		Letter.push_back(a);
//	}
//
//
//	/*while (true)
//	{
//		if (letter.empty())
//			break;
//		
//		Letter;
//
//		string le;
//
//		for (int i = 0; i < letter.size(); i++)
//		{
//			while (letter[i] != ' ')
//			{
//				string s(1, letter[i]);
//				
//				le += s;
//
//				letter.erase(0, i + 1);
//			}
//		}
//
//		Letter.push_back(le);
//
//		Sapperate(letter, Letter);
//	}*/
//}
//
//string solution(string letter) {
//	string answer = "";
//
//	vector<string> Letter;
//
//	std::string delimiter = " ";
//	size_t pos = 0;
//	std::string token;
//	while ((pos = letter.find(delimiter)) != std::string::npos) {
//		token = letter.substr(0, pos);
//		Letter.push_back(token);
//		letter.erase(0, pos + delimiter.length());
//	}
//	Letter.push_back(letter);
//
//	map<string, string> morse =
//	{
//		{"a", ".-"}, {"b", "-..."}, {"c" , "-.-."}, {"d" , "-.."}, {"e" , "."}, {"f" , "..-."},
//		{"g" , "--."}, {"h" , "...."}, {"i" , ".."}, {"j" , ".---"}, {"k" , "-.-"}, {"l" , ".-.."},
//		{"m" , "--"}, {"n" , "-."}, {"o" , "---"},{"p" , ".--."}, {"q" , "--.-"}, {"r" , ".-."},
//		{"s" , "..."}, {"t" , "-"}, {"u", "..-"}, {"v" , "...-"}, {"w" , ".--"}, {"x" , "-..-"},
//		{"y" , "-.--"}, {"z" , "--.."}
//	};
//
//	for (int i = 0; i < Letter.size(); i++)
//	{
//		for (auto iter : morse) {
//			if (iter.second == Letter[i])
//			{
//				answer += iter.first;
//			}
//		}
//	}
//
//	return answer;
//}
//
//using namespace std;
//
//int solution(string before, string after) {
//	int answer = 0;
//	vector<char> a;
//	vector<char> b;
//	for (auto s : before)
//	{
//		b.push_back(s);
//	}
//
//	for (auto s : after)
//	{
//		a.push_back(s);
//	}
//
//	if (before.size() != after.size())
//		answer = 1;
//	else
//	{
//		for (int i = 0; i < b.size(); i++)
//		{
//			for (int j = 0; j < a.size(); j++)
//			{
//				if (b[i] == a[j])
//				{
//					b.erase(b[i], b[i]);
//				}
//			}
//		}
//	}
//
//	return answer;
//}
//
//int main()
//{
//
//	string Letter1 = ".... . .-.. .-.. ---";
//
//	std::cout << solution(Letter1) << std::endl;
//
//	return 0;
//}

#define MAX 8

int answer = 0;
bool visited[MAX] = { 0 };

void dfs(int cnt, int k, vector<vector<int>>& dungeons) 
{
    if (cnt > answer) answer = cnt;

    for (int i = 0; i < dungeons.size(); i++) {
        if (!visited[i] && dungeons[i][0] <= k) {
            visited[i] = true;
            dfs(cnt + 1, k - dungeons[i][1], dungeons);
            visited[i] = false;
        }
    }
}

int solution(int k, vector<vector<int>> dungeons) 
{
    dfs(0, k, dungeons);

    return answer;
};

bool compare(pair<int, int> a, pair<int, int> b)
{
    return a.first > b.first;
}

vector<int> solution(vector<int> emergency) 
{
    vector<int> answer;
    vector<pair<int, int>> pq;

    for (int i = 0; i < emergency.size(); i++)
    {
        pq.push_back({ emergency[i], i + 1 });
    }

    sort(pq.begin(), pq.end(), compare);

    for (int i = 0; i < pq.size(); i++)
    {
        pq[i].second = i + 1;
    }

    for (int i = 0; i < emergency.size(); i++)
    {
        for (int j = 0; j < pq.size(); j++)
        {
            if (emergency[i] == pq[j].first)
                answer.push_back(pq[j].second);
        }
    }

    return answer;
}

int main2()
{
    vector<int> emergency = { 3, 76, 24 };

    vector<int> answer;

    solution(emergency);

    return 0;
}

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <vector>

// 파라미터로 주어지는 문자열은 const로 주어집니다. 변경하려면 문자열을 복사해서 사용하세요.
char* solution(const char* s) {
    // return 값은 malloc 등 동적 할당을 사용해주세요. 할당 길이는 상황에 맞게 변경해주세요.
    char* answer = (char*)malloc(sizeof(char));

    vector<char> v;

    for (auto c : s)
    {
        v.push_back(c);
    }

    return answer;
}

int main3()
{
    string s = "abcabcadc";

    solution(s);
}