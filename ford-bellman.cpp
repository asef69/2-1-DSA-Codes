#include <bits/stdc++.h>
using namespace std;

const int UNREACHABLE = 30000;

class Edge
{
public:
    int u, v;
    int weight;
    Edge(int u, int v, int weight)
    {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> minWeight(n + 1, vector<int>(n + 1, UNREACHABLE));
    
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (c < minWeight[a][b])
        {
            minWeight[a][b] = c;
        }
    }
    
    vector<Edge> edge_list;
    for (int u = 1; u <= n; u++)
    {
        for (int v = 1; v <= n; v++)
        {
            if (minWeight[u][v] != UNREACHABLE)
            {
                edge_list.push_back(Edge(u, v, minWeight[u][v]));
            }
        }
    }
    
    vector<int> dist(n + 1, UNREACHABLE);
    dist[1] = 0;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (auto edge : edge_list)
        {
            int node = edge.u;
            int weight = edge.weight;
            int destination = edge.v;
            
            if (dist[node] != UNREACHABLE && dist[node] + weight < dist[destination])
            {
                dist[destination] = dist[node] + weight;
            }
        }
    }

    for (int i = 1; i <= n; i++)
    {
        cout << dist[i] << " ";
    }
    
    return 0;
}