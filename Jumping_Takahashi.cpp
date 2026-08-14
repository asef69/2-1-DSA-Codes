#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, X;
    cin >> N >> X;

    vector<pair<int, int> > jumps(N);
    for (int i = 0; i < N; ++i) {
        cin >> jumps[i].first >> jumps[i].second;
    }

    vector<bool> dp(X + 1, false);
    dp[0] = true;

    for (int i = 0; i < N; ++i) {
        vector<bool> next(X + 1, false);
        for (int sum = 0; sum <= X; ++sum) {
            if (!dp[sum]) continue;
            if (sum + jumps[i].first <= X) next[sum + jumps[i].first] = true;
            if (sum + jumps[i].second <= X) next[sum + jumps[i].second] = true;
        }
        dp.swap(next);
    }

    cout << (dp[X] ? "Yes" : "No") << '\n';
    return 0;
}