#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

vector<vector<int>> adj;
vector<int> dist;
vector<int> components;

void dijkstraLikeBFS(int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {  // All edges have weight 1
                dist[v] = dist[u] + 1;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    
    adj.resize(n + 1);
    dist.assign(n + 1, INT_MAX);
    
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    // Find connected components using Dijkstra-like approach
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) {  // Not visited
            components.push_back(i);
            dijkstraLikeBFS(i);
        }
    }
    
    cout << components.size() - 1 << endl;
    for (int i = 1; i < components.size(); i++) {
        cout << components[i - 1] << " " << components[i] << endl;
    }
    
    return 0;
}