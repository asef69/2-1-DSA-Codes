#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    long long lo = 1, hi = 1LL * n * n;
    long long need = (1LL * n * n + 1) / 2;
    long long ans = hi;
    while (lo <= hi)
    {
        long long mid = lo + (hi - lo) / 2;
        long long cnt = 0;
        for (long long i = 1; i <= n; ++i)
        {
            long long add = mid / i;
            if (add > n)
                add = n;
            cnt += add;
        }
        if (cnt >= need)
        {
            ans = mid;
            hi = mid - 1;
        }
        else
            lo = mid + 1;
    }
    cout << ans;
}