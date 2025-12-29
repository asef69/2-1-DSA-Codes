#include <bits/stdc++.h>
using namespace std;
bool visited[105];
vector<int> adj_list[1005];
int par[105];
bool cycle;

void dfs(int node, int parent)
{
    visited[node] = true;
    for (int children : adj_list[node])
    {
        if (visited[children] && parent != children)
        {
            cycle = true;
        }
        if (!visited[children])
        {
            dfs(children, node);
        }
    }
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
        adj_list[b].push_back(a);
    }
    memset(visited, false, sizeof(visited));
    cycle = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            dfs(i, -1);
        }
    }
    if (cycle)
        cout << "Cycle available" << endl;
    else
        cout << "Not Cycle" << endl;
}
