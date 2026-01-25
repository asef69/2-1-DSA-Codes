#include <bits/stdc++.h>
using namespace std;

class HopcroftKarp {
private:
    int L, R;
    vector<vector<int>> adj;
    vector<int> matchL, matchR, dist;
    
    bool bfs() {
        queue<int> q;
        for (int u = 0; u < L; u++) {
            if (matchL[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = -1;
            }
        }
        
        bool found = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v : adj[u]) {
                if (matchR[v] == -1) {
                    found = true;
                } else if (dist[matchR[v]] == -1) {
                    dist[matchR[v]] = dist[u] + 1;
                    q.push(matchR[v]);
                }
            }
        }
        return found;
    }
    
    bool dfs(int u) {
        for (int v : adj[u]) {
            if (matchR[v] == -1 || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        dist[u] = -1;
        return false;
    }
    
public:
    HopcroftKarp(int L, int R) : L(L), R(R) {
        adj.resize(L);
        matchL.assign(L, -1);
        matchR.assign(R, -1);
        dist.resize(L);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    int maxMatching() {
        int matching = 0;
        while (bfs()) {
            for (int u = 0; u < L; u++) {
                if (matchL[u] == -1 && dfs(u)) {
                    matching++;
                }
            }
        }
        return matching;
    }
    
    vector<pair<int, int>> getMatchingEdges() {
        vector<pair<int, int>> edges;
        for (int u = 0; u < L; u++) {
            if (matchL[u] != -1) {
                edges.emplace_back(u, matchL[u]);
            }
        }
        return edges;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int L, R, M;
    cin >> L >> R >> M;
    
    HopcroftKarp hk(L, R);
    
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        hk.addEdge(a, b);
    }
    
    int matchingSize = hk.maxMatching();
    vector<pair<int, int>> matchingEdges = hk.getMatchingEdges();
    
    cout << matchingSize << "\n";
    for (auto& edge : matchingEdges) {
        cout << edge.first << " " << edge.second << "\n";
    }
    
    return 0;
}