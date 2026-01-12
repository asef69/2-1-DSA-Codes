#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<int> start(N), target(N);
    
    for (int i = 0; i < N; i++) {
        cin >> start[i];
        start[i]--; // 0-indexed
    }
    
    for (int i = 0; i < N; i++) {
        cin >> target[i];
        target[i]--; // 0-indexed
    }
    
    // Initialize distance matrix
    vector<vector<long long> > dist(N, vector<long long>(N, INF));
    
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
    }
    
    // Floyd-Warshall Algorithm
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Calculate costs for each army
    vector<long long> costs;
    
    for (int i = 0; i < N; i++) {
        long long cost = dist[start[i]][target[i]];
        
        // Only include armies that can reach their target
        if (cost != INF) {
            costs.push_back(cost);
        }
    }
    
    // Sort costs in descending order (relocate expensive armies first to avoid multiplier)
    sort(costs.begin(), costs.end(), greater<long long>());
    
    // Calculate total cost with batching
    long long totalCost = 0;
    int numArmies = costs.size();
    
    for (int i = 0; i < numArmies; i++) {
        int batchNumber = i / K; // Which batch this army belongs to (0-indexed)
        long long multiplier = 1LL << batchNumber; // 2^batchNumber
        totalCost += costs[i] * multiplier;
    }
    
    cout << totalCost << endl;
    
    return 0;
}