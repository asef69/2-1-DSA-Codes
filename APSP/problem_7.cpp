/*
P2.2: Arbitrage Detection with Transaction Fees
Problem Statement:
Determine if arbitrage is possible when each exchange transaction incurs a fixed fee f. For example, exchanging x units results in x * rate * (1 - f) units after fee.

Input Format:

text
n f
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

1 ≤ n ≤ 30

0 ≤ f ≤ 0.1 (10% maximum fee)

0.001 ≤ rate ≤ 1000.0

Rates given with up to 4 decimal places

Output Format:
Output "Yes" if arbitrage is possible, "No" otherwise.

Example:

text
Input:
3 0.001
USD
EUR
GBP
3
USD 0.85 EUR
EUR 0.90 GBP
GBP 1.30 USD

Output:
No
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    double f;
    cin >> n >> f;
    
    map<string, int> currencyIndex;
    vector<string> currencies(n);
    
    for (int i = 0; i < n; i++) {
        cin >> currencies[i];
        currencyIndex[currencies[i]] = i;
    }
    
    int m;
    cin >> m;
    
    // Initialize exchange rate matrix
    // dist[i][j] = maximum amount of currency j we can get from 1 unit of currency i
    vector<vector<double>> dist(n, vector<double>(n, 0.0));
    
    // Initialize diagonal (1 unit of currency i = 1 unit of currency i, no exchange needed)
    for (int i = 0; i < n; i++) {
        dist[i][i] = 1.0;
    }
    
    // Read exchange rates and apply transaction fee
    for (int i = 0; i < m; i++) {
        string src, dst;
        double rate;
        cin >> src >> rate >> dst;
        
        int u = currencyIndex[src];
        int v = currencyIndex[dst];
        
        // Effective rate after transaction fee
        double effectiveRate = rate * (1.0 - f);
        
        // Direct exchange: 1 unit of src = effectiveRate units of dst
        dist[u][v] = max(dist[u][v], effectiveRate);
    }
    
    // Modified Floyd-Warshall for maximum exchange rate
    // dist[i][j] = max amount of currency j obtainable from 1 unit of currency i
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // Going from i to j through k
                if (dist[i][k] > 0 && dist[k][j] > 0) {
                    dist[i][j] = max(dist[i][j], dist[i][k] * dist[k][j]);
                }
            }
        }
    }
    
    // Check for arbitrage opportunity
    bool arbitrageExists = false;
    
    for (int i = 0; i < n; i++) {
        // Check if we can get more than 1 unit back by starting with currency i
        // Use a small epsilon to account for floating point precision
        if (dist[i][i] > 1.0 + 1e-9) {
            arbitrageExists = true;
            break;
        }
    }
    
    if (arbitrageExists) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    
    return 0;
}