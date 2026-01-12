/*
P2.4: Multi-Currency Start Detection
Problem Statement:
For each currency, determine if starting with 1 unit of that currency, you can achieve arbitrage (end with more than 1 unit of the same currency after some sequence of exchanges).

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

Output Format:
List all currencies from which arbitrage is possible, in alphabetical order, one per line. If none, print "None".

Example:

text
Input:
4
USD
EUR
GBP
JPY
5
USD 0.85 EUR
EUR 0.90 GBP
GBP 1.30 USD
USD 110.5 JPY
JPY 0.0092 EUR

Output:
EUR
GBP
USD
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<string> currencies(n);
    map<string, int> idx;
    
    for (int i = 0; i < n; i++) {
        cin >> currencies[i];
        idx[currencies[i]] = i;
    }
    
    int m;
    cin >> m;
    
    // Initialize exchange rate matrix
    vector<vector<double>> dist(n, vector<double>(n, 0.0));
    
    // Each currency to itself = 1.0 (no exchange)
    for (int i = 0; i < n; i++) {
        dist[i][i] = 1.0;
    }
    
    // Read exchange rates
    for (int i = 0; i < m; i++) {
        string src, dst;
        double rate;
        cin >> src >> rate >> dst;
        
        int u = idx[src];
        int v = idx[dst];
        
        dist[u][v] = max(dist[u][v], rate);
    }
    
    // Floyd-Warshall for maximum exchange rates
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] > 0 && dist[k][j] > 0) {
                    dist[i][j] = max(dist[i][j], dist[i][k] * dist[k][j]);
                }
            }
        }
    }
    
    // Find currencies with arbitrage opportunity
    vector<string> arbitrageCurrencies;
    
    for (int i = 0; i < n; i++) {
        // Check if we can get more than 1 unit back
        if (dist[i][i] > 1.0 + 1e-9) {
            arbitrageCurrencies.push_back(currencies[i]);
        }
    }
    
    // Sort alphabetically
    sort(arbitrageCurrencies.begin(), arbitrageCurrencies.end());
    
    // Output
    if (arbitrageCurrencies.empty()) {
        cout << "None" << endl;
    } else {
        for (const string& currency : arbitrageCurrencies) {
            cout << currency << endl;
        }
    }
    
    return 0;
}