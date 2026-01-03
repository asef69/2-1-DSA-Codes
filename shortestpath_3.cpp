#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;

const long long INF = numeric_limits<long long>::max();

struct Edge {
    int from, to;
    long long weight;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q, s;
    bool firstCase = true;
    
    while (cin >> n >> m >> q >> s) {
        if (n == 0 && m == 0 && q == 0 && s == 0) {
            break;
        }
        
        if (!firstCase) {
            cout << "\n";
        }
        firstCase = false;
        
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) {
            cin >> edges[i].from >> edges[i].to >> edges[i].weight;
        }
        
        vector<long long> dist(n, INF);
        dist[s] = 0;
        
        for (int i = 0; i < n - 1; i++) {
            for (const Edge& e : edges) {
                if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[e.from] + e.weight;
                }
            }
        }
        
        vector<bool> inNegativeCycle(n, false);
        for (int i = 0; i < n; i++) {
            for (const Edge& e : edges) {
                if (dist[e.from] != INF && dist[e.from] + e.weight < dist[e.to]) {
                    dist[e.to] = dist[e.from] + e.weight;
                    inNegativeCycle[e.to] = true;
                }
            }
        }

        vector<bool> reachableFromNegativeCycle(n, false);
        for (int i = 0; i < n; i++) {
            if (inNegativeCycle[i] && !reachableFromNegativeCycle[i]) {
                queue<int> q_bfs;
                q_bfs.push(i);
                reachableFromNegativeCycle[i] = true;
                
                while (!q_bfs.empty()) {
                    int u = q_bfs.front();
                    q_bfs.pop();
                    
                    for (const Edge& e : edges) {
                        if (e.from == u && !reachableFromNegativeCycle[e.to]) {
                            reachableFromNegativeCycle[e.to] = true;
                            q_bfs.push(e.to);
                        }
                    }
                }
            }
        }
        
        for (int i = 0; i < q; i++) {
            int target;
            cin >> target;
            
            if (reachableFromNegativeCycle[target]) {
                cout << "-Infinity\n";
            } else if (dist[target] == INF) {
                cout << "Impossible\n";
            } else {
                cout << dist[target] << "\n";
            }
        }
    }
    
    return 0;
}