#include <bits/stdc++.h>
using namespace std;

int main() {
  
    
    int n;
    cin >> n;
        vector<vector<long long> > C(n + 1, vector<long long>(n + 1));
    

    for (int i = 1; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> C[i][j];
        }
    }
    
    for (int a = 1; a <= n - 2; a++) {
        for (int c = a + 2; c <= n; c++) {
            long long direct = C[a][c];
            for (int b = a + 1; b < c; b++) {
                if (C[a][b] + C[b][c] < direct) {
                    cout << "Yes" << endl;
                    return 0;
                }
            }
        }
    }
    
    cout << "No" << endl;
    return 0;
}
