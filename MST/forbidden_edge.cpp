/*
Problem 5: MST with Forbidden Edges
Problem Statement
Given a connected, undirected, weighted graph and a list of forbidden edges, find the minimum spanning tree that does not use any forbidden edges. If no such spanning tree exists, output -1.

Task:
Find the weight of MST without using forbidden edges.

Input Format:

First line: N M F (vertices, edges, forbidden edges)

Next M lines: u v w (edge between u and v with weight w)

Next F lines: idx (1-based index of forbidden edge)

Output Format:

Single integer: weight of MST without forbidden edges, or -1

Constraints:

2 ≤ N ≤ 1000

N-1 ≤ M ≤ 10000

0 ≤ F ≤ M

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
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, f;
    cin >> n >> m >> f;
    
    vector<tuple<int, int, int, bool>> edges; // w, u, v, is_forbidden
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(make_tuple(w, u, v, false));
    }
    
    for(int i = 0; i < f; i++) {
        int idx;
        cin >> idx;
        idx--; 
        if(idx < m) {
            get<3>(edges[idx]) = true;
        }
    }
    
    sort(edges.begin(), edges.end(), 
         [](const auto& a, const auto& b) {
             if(get<3>(a) != get<3>(b)) return get<3>(a) < get<3>(b);
             return get<0>(a) < get<0>(b);
         });
    
    DSU dsu(n);
    int total = 0;
    int edges_used = 0;
    
    for(auto& [w, u, v, forbidden] : edges) {
        if(!forbidden && dsu.unite(u, v)) {
            total += w;
            edges_used++;
        }
    }
    

    if(edges_used < n - 1) {
        dsu = DSU(n); 
        
        sort(edges.begin(), edges.end(),
             [](const auto& a, const auto& b) {
                 return get<0>(a) < get<0>(b);
             });
        
        total = 0;
        edges_used = 0;
        
        for(auto& [w, u, v, forbidden] : edges) {
            if(dsu.unite(u, v)) {
                total += w;
                edges_used++;
            }
        }
    }
    
    cout << (edges_used == n - 1 ? total : -1) << "\n";
    
    return 0;
}