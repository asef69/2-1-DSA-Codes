/*
P2.5: Time-Limited Arbitrage
Problem Statement:
Determine if arbitrage is possible within at most k exchanges (transactions). You can start with any currency. If arbitrage is possible, also output the minimum number of exchanges needed to achieve it.

Input Format:

text
n k
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

1 ≤ n ≤ 50

1 ≤ k ≤ 10

1 ≤ m ≤ 500

Output Format:
If arbitrage is possible within k exchanges: "Yes x" where x is minimum exchanges needed
Otherwise: "No"

Example:

text
Input:
3 5
USD
EUR
GBP
3
USD 0.85 EUR
EUR 0.90 GBP
GBP 1.30 USD

Output:
Yes 3
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    
    vector<string> currencies(n);
    map<string, int> idx;
    
    for (int i = 0; i < n; i++) {
        cin >> currencies[i];
        idx[currencies[i]] = i;
    }
    
    int m;
    cin >> m;
    
    // dist[i][j][steps] = max amount of currency j from 1 unit of currency i in exactly 'steps' exchanges
    vector<vector<vector<double>>> dist(n, vector<vector<double>>(n, vector<double>(k + 1, 0.0)));
    
    // Base case: 0 exchanges means same currency
    for (int i = 0; i < n; i++) {
        dist[i][i][0] = 1.0;
    }
    
    // Store direct edges
    vector<tuple<int, int, double>> edges;
    
    for (int i = 0; i < m; i++) {
        string src, dst;
        double rate;
        cin >> src >> rate >> dst;
        
        int u = idx[src];
        int v = idx[dst];
        
        edges.push_back(make_tuple(u, v, rate));
        // 1 exchange: direct conversion
        dist[u][v][1] = max(dist[u][v][1], rate);
    }
    
    // Dynamic programming: build paths with increasing number of exchanges
    for (int steps = 2; steps <= k; steps++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Try extending (steps-1) exchange path with 1 more exchange
                for (auto& [u, v, rate] : edges) {
                    if (dist[i][u][steps - 1] > 0) {
                        dist[i][v][steps] = max(dist[i][v][steps], dist[i][u][steps - 1] * rate);
                    }
                }
            }
        }
    }
    
    // Check for arbitrage opportunity
    int minExchanges = -1;
    
    for (int i = 0; i < n; i++) {
        for (int steps = 1; steps <= k; steps++) {
            if (dist[i][i][steps] > 1.0 + 1e-9) {
                if (minExchanges == -1 || steps < minExchanges) {
                    minExchanges = steps;
                }
            }
        }
    }
    
    if (minExchanges != -1) {
        cout << "Yes " << minExchanges << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}