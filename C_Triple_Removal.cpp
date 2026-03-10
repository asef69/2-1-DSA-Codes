#include <bits/stdc++.h>
using namespace std;

int main() {
   

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        vector<int> a(n + 1, 0);
        vector<int> prefOne(n + 1, 0);
        vector<int> prefSameAdj(n + 1, 0);

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            prefOne[i] = prefOne[i - 1] + (a[i] == 1);
            prefSameAdj[i] = prefSameAdj[i - 1] + (i > 1 && a[i] == a[i - 1]);
        }

        while (q--) {
            int l, r;
            cin >> l >> r;

            int len = r - l + 1;
            int ones = prefOne[r] - prefOne[l - 1];
            int zeros = len - ones;

            if (ones % 3 != 0 || zeros % 3 != 0) {
                cout << -1 << '\n';
                continue;
            }

            int ans = len / 3;

            int sameAdjInside = prefSameAdj[r] - prefSameAdj[l];
            if (sameAdjInside == 0) {
                ans++;
            }

            cout << ans << '\n';
        }
    }

    return 0;
}