/*
P1.5: Dynamic Road Network with Toggle Roads
Problem Statement:
You have a network of cities where roads can be toggled open/closed. Initially, all roads are open. Process q queries of two types:

1 a b: Find shortest distance between cities a and b with current road status

2 x: Toggle the x-th road (close if open, open if closed)

Input Format:

text
n m q
a1 b1 c1
a2 b2 c2
...
am bm cm
type1 param1 [param2]
type2 param1
...
typeq param1 [param2]
Constraints:

1 ≤ n ≤ 100

1 ≤ m ≤ 500

1 ≤ q ≤ 2000

Type 1 queries: 1 ≤ a, b ≤ n

Type 2 queries: 1 ≤ x ≤ m

Output Format:
For each type 1 query, output the shortest distance or -1 if no path exists.

Example:

text
Input:
4 4 6
1 2 5
1 3 9
2 3 3
3 4 2
1 1 4
2 3
1 1 4
2 2
1 1 4
1 2 4

*/

#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m, q;
    cin >> n >> m >> q;
    
    // Store all roads with their endpoints and weights
    vector<tuple<int, int, long long>> roads(m);
    vector<bool> roadOpen(m, true); // Initially all roads are open
    
    for (int i = 0; i < m; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--; b--; // 0-indexed
        roads[i] = make_tuple(a, b, c);
    }
    
    // Function to compute Floyd-Warshall with current road status
    auto computeFloydWarshall = [&]() {
        vector<vector<long long>> dist(n, vector<long long>(n, INF));
        
        // Initialize diagonal
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        
        // Add edges that are currently open
        for (int i = 0; i < m; i++) {
            if (roadOpen[i]) {
                int a, b;
                long long c;
                tie(a, b, c) = roads[i];
                dist[a][b] = min(dist[a][b], c);
                dist[b][a] = min(dist[b][a], c); // Bidirectional
            }
        }
        
        // Floyd-Warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        return dist;
    };
    
    // Initial computation
    vector<vector<long long>> dist = computeFloydWarshall();
    
    // Process queries
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            // Query: Find shortest distance
            int a, b;
            cin >> a >> b;
            a--; b--; // 0-indexed
            
            if (dist[a][b] == INF) {
                cout << -1 << endl;
            } else {
                cout << dist[a][b] << endl;
            }
        } else {
            // Toggle road
            int x;
            cin >> x;
            x--; // 0-indexed
            
            roadOpen[x] = !roadOpen[x];
            
            // Recompute Floyd-Warshall
            dist = computeFloydWarshall();
        }
    }
    
    return 0;
}