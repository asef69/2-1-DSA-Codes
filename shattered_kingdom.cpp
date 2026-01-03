#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, m, k, b, e;
    cin >> n >> m >> k >> b >> e;
    
    vector<int> capitals(k);
    for (int i = 0; i < k; i++) cin >> capitals[i];
    
    vector<bool> blocked_cities(n + 1, false);
    for (int i = 0; i < b; i++)
    {
        int a; cin >> a;
        blocked_cities[a] = true;
    }
    
    vector<int> emergency(e);
    for (int i = 0; i < e; i++) cin >> emergency[i];

    vector<vector<pair<int, long long>>> adj_list(n + 1);
    for (int i = 0; i < m; i++)
    {
        int u, v; long long w;
        cin >> u >> v >> w;
        if (!blocked_cities[u] && !blocked_cities[v])
            adj_list[u].push_back(make_pair(v, w));
    }

    
    for (int cap : capitals)
    {
        if (!blocked_cities[cap])
            adj_list[0].push_back(make_pair(cap, 0));
    }

    vector<long long> dist(n + 1, LLONG_MAX);
    dist[0] = 0;
    
    for (int i = 0; i < n; i++)
    {
        bool updated = false;
        for (int u = 0; u <= n; u++)
        {
            if (dist[u] == LLONG_MAX) continue;
            for (size_t j = 0; j < adj_list[u].size(); j++)
            {
                int node = adj_list[u][j].first;
                long long weight = adj_list[u][j].second;
                if (dist[u] + weight < dist[node])
                {
                    dist[node] = dist[u] + weight;
                    updated = true;
                }
            }
        }
        if (!updated) break; 
    }
    
    
    for (int u = 0; u <= n; u++)
    {
        if (dist[u] == LLONG_MAX) continue;
        for (size_t j = 0; j < adj_list[u].size(); j++)
        {
            int node = adj_list[u][j].first;
            long long weight = adj_list[u][j].second;
            if (dist[u] + weight < dist[node])
            {
                cout << "Abyss Detected";
                return 0;
            }
        }
    }
    
    for (int target : emergency)
    {
        if (blocked_cities[target] || dist[target] == LLONG_MAX)
            cout << "INF\n";
        else
            cout << dist[target] << "\n";
    }
    
    return 0;
}