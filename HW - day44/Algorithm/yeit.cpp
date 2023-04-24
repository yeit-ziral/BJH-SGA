#include <string>
#include <vector>
#include <queue>
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

const int INF = 987654321;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int solution(vector<vector<int>> maps)
{
    int n = maps.size();
    int m = maps[0].size();
    
    vector<vector<int>> dist(n, vector<int>(m, INF));
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    dist[0][0] = 1;
    visited[0][0] = true;

    queue<pair<int, int>> q;
    q.push(make_pair(0, 0));

    while (!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;

        q.pop();

        for (int i = i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m)
                continue;

            if (maps[nx][ny] == 0)
                continue;

            if (!visited[nx][ny])
            {
                visited[nx][ny] == true;
                dist[nx][ny] = dist[x][y] + 1;
                q.push(make_pair(nx, ny));
            }
        }
    }

    vector<vector<bool>> discovered;
    vector<vector<int>> 

    int answer = dist[n - 1][m - 1];

    if (answer == INF)
        answer = -1;

    return answer;
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