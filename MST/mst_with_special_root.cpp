/*
Problem 1: MST with Special Root
Problem Statement
In a remote archipelago of N islands (3 ≤ N ≤ 1000), you need to connect all islands with underwater power cables. There are M potential cable routes (N ≤ M ≤ 10000), each with a construction cost. The power generator is located on a specific root island. Your task is to find the minimum spanning tree (MST) that connects all islands, ensuring the generator island (root) is properly connected.

Task:
Implement Prim's algorithm to find the MST starting from the given root node.

Input Format:

First line: N M (number of vertices and edges)

Next M lines: u v w (undirected edge between u and v with weight w)

Last line: r (root node, 0-indexed)

Output Format:

First line: "Total weight X" where X is the MST weight

Second line: "Root node R" where R is the root

Next (N-1) lines: u v (edges in the MST, in any order)

Constraints:

3 ≤ N ≤ 1000

N ≤ M ≤ 10000

0 ≤ u, v < N

1 ≤ w ≤ 1000

0 ≤ r < N
*/
#include <bits/stdc++.h>
using namespace std;
void prim_algorithm(long long root, vector<vector<pair<long long, long long> > > &adj, long long n) {
    vector<bool> visited(n, false);
    priority_queue<pair<long long, long long>, vector<pair<long long, long long> >, greater<pair<long long, long long> > > pq;
    vector<pair<long long, long long> > MSTedges;
    vector<long long> parent(n, -1);
    vector<long long> minEdge(n, LLONG_MAX);

    long long totalWeight = 0;
    pq.push(make_pair(0, root));
    minEdge[root] = 0;

    while (!pq.empty()) {
        pair<long long, long long> edge = pq.top();
        pq.pop();

        long long current_node = edge.second;
        long long current_weight = edge.first;

        if (visited[current_node])
            continue;

        if (current_weight != minEdge[current_node])
            continue;

        visited[current_node] = true;
        totalWeight += current_weight;

        if (parent[current_node] != -1) {
            MSTedges.push_back(make_pair(parent[current_node], current_node));
        }

        for (vector<pair<long long, long long> >::iterator it = adj[current_node].begin(); it != adj[current_node].end(); ++it) {
            pair<long long, long long> neighbor = *it;
            long long neighbor_node = neighbor.first;
            long long neighbor_weight = neighbor.second;

            if (!visited[neighbor_node] && neighbor_weight < minEdge[neighbor_node]) {
                minEdge[neighbor_node] = neighbor_weight;
                parent[neighbor_node] = current_node;
                pq.push(make_pair(neighbor_weight, neighbor_node));
            }
        }
    }

    cout << "Total weight " << totalWeight << endl;
    cout << "Root node " << root << endl;
    for (vector<pair<long long, long long> >::iterator it = MSTedges.begin(); it != MSTedges.end(); ++it) {
        pair<long long, long long> mst_edge = *it;
        cout << mst_edge.first << " " << mst_edge.second << endl;
    }
}
int main() {
    long long n, m;
    cin >> n >> m;
    
    vector<vector<pair<long long, long long> > > adj(n);
    vector<pair<long long, pair<long long, long long> > > edges;

    for (long long i = 0; i < m; i++) {
        long long u, v, w;
        cin >> u >> v >> w;
        
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
        
        edges.push_back(make_pair(w, make_pair(u, v)));
    }

    long long root;
    cin >> root;

    cout << "Prim's Algorithm:" << endl;
    prim_algorithm(root, adj, n);
    
    
}