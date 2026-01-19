/*
Problem 8: Minimum Spanning Forest
Problem Statement
Given an undirected weighted graph that may not be connected, you need to create exactly K connected components (a spanning forest with K trees) with minimum total weight.

Task:
Find the minimum total weight to connect the graph into exactly K components.

Input Format:

First line: N M K (vertices, edges, desired components)

Next M lines: u v w (edge between u and v with weight w)

Output Format:

Single integer: minimum total weight

Constraints:

1 ≤ N ≤ 1000

0 ≤ M ≤ 10000

1 ≤ K ≤ N

1 ≤ u, v ≤ N

1 ≤ w ≤ 1000
*/
#include <bits/stdc++.h>
using namespace std;

class DSU {
    vector<int> parent, rank;
    int components;
public:
    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        components = n;
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
        components--;
        return true;
    }
    
    int get_components() {
        return components;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, k;
    cin >> n >> m >> k;
    
    vector<tuple<int, int, int>> edges;
    for(int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back(make_tuple(w, u, v));
    }
    
    sort(edges.begin(), edges.end());
    
    DSU dsu(n);
    int total = 0;
    
    for(auto& [w, u, v] : edges) {
        if(dsu.get_components() <= k) break;
        
        if(dsu.unite(u, v)) {
            total += w;
        }
    }
    
    cout << total << "\n";
    
    return 0;
}