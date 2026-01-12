/*
Problem Set 2: Currency Arbitrage Problems
P2.1: Maximum Arbitrage Profit Percentage
Problem Statement:
Given a list of currency exchange rates, determine the maximum possible profit percentage that can be achieved starting with 1 unit of any currency, allowing any number of trades. Profit is calculated as: (final_amount - 1) * 100%.

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

1 ≤ n ≤ 100

1 ≤ m ≤ n²

0.001 ≤ rate ≤ 1000.0

Currency names contain no spaces, up to 10 characters

Output Format:
Output the maximum profit percentage rounded to 2 decimal places. If no arbitrage is possible, output 0.00.

Example:

text
Input:
3
USD
EUR
GBP
3
USD 0.85 EUR
EUR 0.90 GBP
GBP 1.30 USD

Output:
0.50
Explanation:
USD→EUR→GBP→USD: 1 × 0.85 × 0.90 × 1.30 = 0.9945 (loss)
But maybe EUR→GBP→USD→EUR: 1 × 0.90 × 1.30 × (1/0.85) = 1.376...
Wait need to compute properly...
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
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
    
    // Initialize diagonal (1 unit of currency i = 1 unit of currency i)
    for (int i = 0; i < n; i++) {
        dist[i][i] = 1.0;
    }
    
    // Read exchange rates
    for (int i = 0; i < m; i++) {
        string src, dst;
        double rate;
        cin >> src >> rate >> dst;
        
        int u = currencyIndex[src];
        int v = currencyIndex[dst];
        
        // Direct exchange: 1 unit of src = rate units of dst
        dist[u][v] = max(dist[u][v], rate);
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
    
    // Find maximum profit by checking all cycles
    double maxProfit = 0.0;
    
    for (int i = 0; i < n; i++) {
        // Check if we can get more than 1 unit back by starting with currency i
        if (dist[i][i] > 1.0) {
            double profit = (dist[i][i] - 1.0) * 100.0;
            maxProfit = max(maxProfit, profit);
        }
    }
    
    cout << fixed << setprecision(2) << maxProfit << endl;
    
    return 0;
}
