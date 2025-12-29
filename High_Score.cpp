#include <bits/stdc++.h>
using namespace std;
class Edge
{
public:
    int a, b;
    long long c;
    Edge(int a, int b, long long c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    vector<Edge> edge_list;
    while (m--)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        edge_list.push_back(Edge(a, b, c));
    }
    vector<long long> dist(n + 1, LLONG_MIN);
    dist[1] = 0;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (auto edge : edge_list)
        {
            if(dist[edge.a] != LLONG_MIN && dist[edge.a] + edge.c > dist[edge.b]){
                dist[edge.b] = dist[edge.a] + edge.c;
            }
        }
    }
    
    vector<bool> in_cycle(n + 1, false);
    for (int i = 0; i < n; i++)
    {
        for (auto edge : edge_list)
        {
            if(dist[edge.a] != LLONG_MIN && dist[edge.a] + edge.c > dist[edge.b]){
                dist[edge.b] = dist[edge.a] + edge.c;
                in_cycle[edge.b] = true;
            }
            if(in_cycle[edge.a]) in_cycle[edge.b] = true;
        }
    }
    
    if(in_cycle[n]) cout << -1 << endl;
    else cout << dist[n] << endl;
}