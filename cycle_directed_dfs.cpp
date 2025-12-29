#include <bits/stdc++.h>
using namespace std;

vector<int> adj_list[1005];
bool visited[105];
bool recStack[105];
bool cycle;

void dfs(int node)
{
    visited[node] = true;
    recStack[node] = true;

    for (int neighbor : adj_list[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor);
        }
        else if (recStack[neighbor])
        {
            cycle = true;
        } 
    }

    recStack[node] = false;
}

int main()
{
    int n, e;
    cin >> n >> e;

    while (e--)
    {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
    }

    memset(visited, false, sizeof(visited));
    memset(recStack, false, sizeof(recStack));
    cycle = false;

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }

    if (cycle)
        cout << "Cycle available" << endl;
    else
        cout << "Not Cycle" << endl;

    return 0;
}
