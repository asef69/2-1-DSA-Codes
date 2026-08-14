#include <bits/stdc++.h>
using namespace std;
int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        long long l = 0, r = min<long long>(2000000000LL, 2 * n);

        while (l < r)
        {
            long long mid = l + (r - l + 1) / 2;
            __int128 val = (__int128)mid * (mid - 1) / 2;
            if (val <= n)
                l = mid;
            else
                r = mid - 1;
        }
        long long k = l;
        __int128 c = (__int128)k * (k - 1) / 2;
        long long y = (long long)(n - c); // number of doubles needed (<= k)
        long long ans = k + y;
        cout << ans << '\n';
    }
}