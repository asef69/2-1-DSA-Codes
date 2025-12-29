#include <bits/stdc++.h>
using namespace std;
bool visited[105];
vector<int> adj_list[1005];
int par[105];
bool cycle;
void bfs(int source)
{
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty())
    {
        int parent = q.front();
        q.pop();
        for (int children : adj_list[parent])
        {
            if (visited[children] && par[parent] != children)
            {
                cycle = true;
            }
            if (visited[children] == false)
            {
                q.push(children);
                visited[children] = true;
                par[children] = parent;
            }
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
    memset(par, -1, sizeof(par));
    cycle = false;
    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            bfs(i);
        }
    }
    if (cycle)
        cout << "Cycle available" << endl;
    else
        cout << "Not Cycle" << endl;
}