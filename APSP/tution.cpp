#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, M, K, X;
    cin >> N >> M >> K >> X;
    
    vector<int> lordCity(K);
    for (int i = 0; i < K; i++) {
        cin >> lordCity[i];
        lordCity[i]--; // 0-indexed
    }
    
    vector<long long> hourlyRate(K);
    for (int i = 0; i < K; i++) {
        cin >> hourlyRate[i];
    }
    
    // Initialize distance and next matrices
    vector<vector<long long> > dist(N, vector<long long>(N, INF));
    vector<vector<int> > next(N, vector<int>(N, -1));
    
    for (int i = 0; i < N; i++) {
        dist[i][i] = 0;
        next[i][i] = i;
    }
    
    // Read edges
    for (int i = 0; i < M; i++) {
        int u, v;
        long long t;
        cin >> u >> v >> t;
        u--; v--; // 0-indexed
        
        if (t < dist[u][v]) {
            dist[u][v] = t;
            dist[v][u] = t;
            next[u][v] = v;
            next[v][u] = u;
        }
    }
    
    // Floyd-Warshall Algorithm
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
    
    // Find best meeting city
    int bestCity = -1;
    long long minCost = INF;
    long long bestMaxTime = 0;
    
    for (int city = 0; city < N; city++) {
        bool canReach = true;
        long long totalCost = 0;
        long long maxTime = 0;
        
        for (int lord = 0; lord < K; lord++) {
            long long travelTime = dist[lordCity[lord]][city];
            
            if (travelTime == INF || travelTime > X) {
                canReach = false;
                break;
            }
            
            totalCost += travelTime * hourlyRate[lord];
            maxTime = max(maxTime, travelTime);
        }
        
        if (canReach) {
            if (totalCost < minCost) {
                minCost = totalCost;
                bestCity = city;
                bestMaxTime = maxTime;
            }
        }
    }
    
    if (bestCity == -1) {
        cout << "No meeting" << endl;
        return 0;
    }
    
    // Output results
    cout << (bestCity + 1) << " " << minCost << " " << bestMaxTime << endl;
    
    // Reconstruct and print paths
    for (int lord = 0; lord < K; lord++) {
        int start = lordCity[lord];
        int end = bestCity;
        
        if (start == end) {
            cout << (start + 1) << " 0" << endl;
        } else {
            vector<int> path;
            int curr = start;
            path.push_back(curr);
            
            while (curr != end) {
                curr = next[curr][end];
                path.push_back(curr);
            }
            
            // Print path
            for (int i = 0; i < path.size(); i++) {
                if (i > 0) cout << " -> ";
                cout << (path[i] + 1);
            }
            
            long long cost = dist[start][end] * hourlyRate[lord];
            cout << " " << cost << endl;
        }
    }
    
    return 0;
}