/*
P2.3: Find All Arbitrage Cycles
Problem Statement:
Given exchange rates, find all distinct currency cycles that yield profit (final amount > 1.0). A cycle is a sequence of currencies starting and ending with the same currency. Two cycles are considered the same if they are rotations of each other.

Input Format:

text
n
currency1
currency2
...
currencyN
m
src1 rate1 dst1
src2 rate2 dst2
...
srcm ratem dstm
Constraints:

1 ≤ n ≤ 20

1 ≤ m ≤ 100

0.001 ≤ rate ≤ 1000.0

Output Format:
First line: number of distinct arbitrage cycles
For each cycle: print the cycle as space-separated currency names (including start currency repeated at end)

Example:

text
Input:
4
USD
EUR
GBP
JPY
6
USD 0.85 EUR
EUR 0.90 GBP
GBP 1.30 USD
USD 110.5 JPY
JPY 0.0092 EUR
EUR 1.18 USD

Output:
2
USD EUR GBP USD
USD JPY EUR USD

*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> currencies;
vector<vector<double>> graph;
set<vector<string>> allCycles;

// Check if cycle has profit
bool hasProfitCycle(vector<int>& cycle) {
    double product = 1.0;
    for (int i = 0; i < cycle.size() - 1; i++) {
        product *= graph[cycle[i]][cycle[i + 1]];
    }
    return product > 1.0000001;
}

// Normalize cycle to avoid duplicates
vector<string> normalizeCycle(vector<int>& cycle) {
    int n = cycle.size() - 1;
    vector<string> best;
    
    for (int start = 0; start < n; start++) {
        vector<string> current;
        for (int i = 0; i < n; i++) {
            current.push_back(currencies[cycle[(start + i) % n]]);
        }
        current.push_back(current[0]);
        
        if (best.empty() || current < best) {
            best = current;
        }
    }
    return best;
}

// Find cycles using DFS
void dfs(int start, int curr, vector<int>& path, vector<bool>& visited) {
    if (path.size() > n) return; // Limit depth
    
    // Found a cycle back to start
    if (curr == start && path.size() > 1) {
        if (hasProfitCycle(path)) {
            vector<string> normalized = normalizeCycle(path);
            allCycles.insert(normalized);
        }
        return;
    }
    
    // Try all neighbors
    for (int next = 0; next < n; next++) {
        if (graph[curr][next] > 0) {
            // Can only visit each node once (except closing cycle at start)
            if (!visited[next] || next == start) {
                visited[next] = true;
                path.push_back(next);
                
                dfs(start, next, path, visited);
                
                path.pop_back();
                if (next != start) visited[next] = false;
            }
        }
    }
}

int main() {
    cin >> n;
    
    currencies.resize(n);
    map<string, int> idx;
    
    for (int i = 0; i < n; i++) {
        cin >> currencies[i];
        idx[currencies[i]] = i;
    }
    
    int m;
    cin >> m;
    
    graph.assign(n, vector<double>(n, 0));
    
    for (int i = 0; i < m; i++) {
        string src, dst;
        double rate;
        cin >> src >> rate >> dst;
        graph[idx[src]][idx[dst]] = max(graph[idx[src]][idx[dst]], rate);
    }
    
    // Find cycles from each currency
    for (int start = 0; start < n; start++) {
        vector<int> path = {start};
        vector<bool> visited(n, false);
        visited[start] = true;
        dfs(start, start, path, visited);
    }
    
    // Output
    cout << allCycles.size() << endl;
    for (auto& cycle : allCycles) {
        for (int i = 0; i < cycle.size(); i++) {
            if (i > 0) cout << " ";
            cout << cycle[i];
        }
        cout << endl;
    }
    
    return 0;
}