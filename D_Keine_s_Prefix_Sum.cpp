#include <bits/stdc++.h>
using namespace std;

int solve(const vector<int>& arr, int n) {
    vector<long long> pref(2 * n + 1, 0);

    for (int i = 0; i < 2 * n; i++) {
        pref[i + 1] = pref[i] + arr[i % n];
    }

    deque<int> dq;
    int good_count = 0;

    for (int i = 1; i <= 2 * n; i++) {
        while (!dq.empty() && pref[dq.back()] >= pref[i]) {
            dq.pop_back();
        }
        dq.push_back(i);

        if (i >= n) {
            int start = i - n;

            while (!dq.empty() && dq.front() <= start) {
                dq.pop_front();
            }

            if (start < n && !dq.empty() && pref[dq.front()] >= pref[start]) {
                good_count++;
            }
        }
    }

    return good_count;
}

int main() {


    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << solve(arr, n) << '\n';
    return 0;
}