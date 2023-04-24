#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

vector<string> path;
vector<bool> visited;


void dfs(string cur, vector<vector<string>> tickets)
{
    if (all_of(visited.begin(), visited.end(), [](const bool& value)->bool {return value == true; }))
        return;

    path.push_back(cur);

    for (int i = 0; i < tickets.size(); i++)
        if (!visited[i] && tickets[i][0] == cur)
        {
            visited[i] == true;
            cnt++;
            dfs(tickets[i][1], tickets);

            if (!flag)
            {
                answer.pop_back();
                visited[i] == true;
            }
        }
}

vector<string> solution(vector<vector<string>> tickets) {
    sort(tickets.begin(), tickets.end());
    dfs("ICN", tickets);
    return answer;
}

int Yeit()
{
    vector<vector<string>> tickets = { {"ICN", "SFO"},{"ICN", "ATL"},{"SFO", "ATL"},{"ATL", "ICN"}, {"ATL", "SFO"} };

    for (int i = 0; i < solution(tickets).size(); i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << solution(tickets)[i][j] << endl;
        }
    }
    
    return 0;
}