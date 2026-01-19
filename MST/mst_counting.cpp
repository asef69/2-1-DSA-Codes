/*
Problem 6: MST Counting
Problem Statement
Given a connected, undirected, weighted graph, count how many different minimum spanning trees exist. Two MSTs are considered different if they have different sets of edges.

Task:
Count the number of distinct MSTs.

Input Format:

First line: N M (number of vertices and edges)

Next M lines: u v w (edge between u and v with weight w)

Output Format:

Single integer: number of distinct MSTs

Constraints:

2 ≤ N ≤ 50

N-1 ≤ M ≤ 200

1 ≤ u, v ≤ N

1 ≤ w ≤ 1000
*/
#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if(parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if(x == y) return false;
        
        if(rank[x] < rank[y]) {
            parent[x] = y;
        } else if(rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[y] = x;
            rank[x]++;
        }
        return true;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    vector<tuple<int, int, int>> edges;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(make_tuple(w, u, v));
    }
    
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    long long total_ways = 1;
    
    int i = 0;
    while(i < m) {
        int j = i;
        while(j < m && get<0>(edges[j]) == get<0>(edges[i])) {
            j++;
        }
        map<int, vector<int>> component_edges;
        for(int k = i; k < j; k++) {
            auto [w, u, v] = edges[k];
            int root_u = dsu.find(u);
            int root_v = dsu.find(v);
            
            if(root_u != root_v) {
                int comp = min(root_u, root_v) * (n + 1) + max(root_u, root_v);
                component_edges[comp].push_back(k);
            }
        }
        
        for(auto& [comp, edge_list] : component_edges) {
            if(edge_list.size() > 1) {
                total_ways *= edge_list.size();
            }
        }
        
        for(int k = i; k < j; k++) {
            auto [w, u, v] = edges[k];
            dsu.unite(u, v);
        }
        
        i = j;
    }
    
    cout << total_ways << "\n";
    
    return 0;
}