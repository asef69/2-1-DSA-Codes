#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> adj_list[105];
int dis[105];

void dijkstra(int source)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({source, 0});
    dis[source] = 0;
    while (!q.empty())
    {
        pair<int, int> par = q.top();
        q.pop();
        int par_node = par.first;
        int par_dist = par.second;
        for (auto child : adj_list[par_node])
        {
            int child_node = child.first;
            int child_dist = child.second;
            if (par_dist + child_dist < dis[child_node])
            {
                dis[child_node] = par_dist + child_dist;
                q.push({child_node, dis[child_node]});
            }
        }
    }
}
int main()
{
    int n, m, source;
    cin >> n >> m >> source;

    for (int i = 0; i <= n; i++)
    {
        dis[i] = INT_MAX;
    }

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        adj_list[u].push_back({v, w});
    }

    dijkstra(source);

    for (int i = 0; i < n; i++)
    {
        cout << dis[i] << "\n";
    }

    return 0;
}