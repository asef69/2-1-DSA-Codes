#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<int> capacity(N);
    vector<bool> underMaintenance(N, false);
    
    for (int i = 0; i < N; i++) {
        cin >> capacity[i];
        if (capacity[i] == -1) {
            underMaintenance[i] = true;
        }
    }
    
    // Initialize distance matrix
    vector<vector<long long>> dist(N, vector<long long>(N, INF));
    
    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
    }
    
    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--; v--; // 0-indexed
        
        dist[u][v] = min(dist[u][v], w);
        dist[v][u] = min(dist[v][u], w);
    }
    
    // Floyd-Warshall Algorithm
    // Don't allow paths through labs under maintenance
    for (int k = 0; k < N; k++) {
        // Skip if this intermediate node is under maintenance
        if (underMaintenance[k]) continue;
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    int Q;
    cin >> Q;
    
    vector<int> queries(Q);
    for (int i = 0; i < Q; i++) {
        cin >> queries[i];
        queries[i]--; // 0-indexed
    }
    
    // Process each query
    for (int q = 0; q < Q; q++) {
        int startLab = queries[q];
        
        // Create a copy of capacities for this query
        vector<int> currentCapacity = capacity;
        
        vector<long long> results;
        
        // Process K students
        for (int student = 0; student < K; student++) {
            long long minCost = INF;
            int bestLab = -1;
            
            // Find the lab with minimum cost
            for (int lab = 0; lab < N; lab++) {
                // Check if lab is available
                if (underMaintenance[lab]) continue;
                if (currentCapacity[lab] <= 0) continue;
                
                // Check if reachable
                if (dist[startLab][lab] == INF) continue;
                
                // Check if this is better
                if (dist[startLab][lab] < minCost) {
                    minCost = dist[startLab][lab];
                    bestLab = lab;
                }
            }
            
            if (bestLab == -1) {
                results.push_back(-1);
            } else {
                results.push_back(minCost);
                currentCapacity[bestLab]--;
            }
        }
        
        // Output results for this query
        for (int i = 0; i < K; i++) {
            if (i > 0) cout << " ";
            cout << results[i];
        }
        cout << endl;
    }
    
    return 0;
}