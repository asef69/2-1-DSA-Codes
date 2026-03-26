#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) {
        pos[nums[i]] = i;
    }
    int rounds = 1;
    for (int i = 2; i <= n; ++i) {
        if (pos[i] < pos[i - 1]) {
            ++rounds;
        }
    }
    cout << rounds << endl;
    return 0;
}
