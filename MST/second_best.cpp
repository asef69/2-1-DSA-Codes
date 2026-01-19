#include <bits/stdc++.h>
using namespace std;

class DSU
{
    vector<int> parent, rank;

public:
    DSU(int n)
    {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for (int i = 1; i <= n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return false;

        if (rank[x] < rank[y])
        {
            parent[x] = y;
        }
        else if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else
        {
            parent[y] = x;
            rank[x]++;
        }
        return true;
    }
};

int find_mst_weight(int n, vector<tuple<int, int, int>> &edges, int skip_edge = -1)
{
    DSU dsu(n);
    vector<tuple<int, int, int>> sorted_edges = edges;

    sort(sorted_edges.begin(), sorted_edges.end());

    int total = 0;
    int edges_used = 0;

    for (int i = 0; i < sorted_edges.size(); i++)
    {
        if (i == skip_edge)
            continue;

        auto [w, u, v] = sorted_edges[i];
        if (dsu.unite(u, v))
        {
            total += w;
            edges_used++;
        }
    }

    return (edges_used == n - 1) ? total : INT_MAX;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges; 
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(make_tuple(w, u, v));
    }

    
    vector<tuple<int, int, int>> sorted_edges = edges;
    sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(n);
    vector<int> mst_edge_indices;
    vector<bool> in_mst(m, false);

    for (int i = 0; i < sorted_edges.size(); i++)
    {
        auto [w, u, v] = sorted_edges[i];
        if (dsu.unite(u, v))
        {
            mst_edge_indices.push_back(i);

            for (int j = 0; j < edges.size(); j++)
            {
                if (edges[j] == sorted_edges[i])
                {
                    in_mst[j] = true;
                    break;
                }
            }
        }
    }

    int mst_weight = find_mst_weight(n, sorted_edges);
    int second_best = INT_MAX;

    for (int i = 0; i < mst_edge_indices.size(); i++)
    {
        int skip_idx = mst_edge_indices[i];
        int candidate = find_mst_weight(n, sorted_edges, skip_idx);
        second_best = min(second_best, candidate);
    }

    cout << (second_best == INT_MAX ? mst_weight : second_best) << "\n";

    return 0;
}