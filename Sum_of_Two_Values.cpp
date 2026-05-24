#include <bits/stdc++.h>
using namespace std;
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
void solve(vector<int> &arr, int n, int target)
{
    unordered_map<int, int, custom_hash> seen;
    for (int i = 0; i < n; i++)
    {
        int compliment = target - arr[i];
        if (seen.count(compliment) > 0)
        {
            cout << seen[compliment] << " " << i + 1 << endl;
            return;
        }
        seen[arr[i]] = i + 1;
    }
    cout << "IMPOSSIBLE" << endl;
    return;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, target;
    cin >> n >> target;
    vector<int> arr;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }
    solve(arr, n, target);
}