#include <bits/stdc++.h>
using namespace std;
int main()
{
    long long n, k;
    cin >> n >> k;
    if (k == 1)
    {
        cout << n << endl;
        return 0;
    }
    long long x = 1;
    while (x < n)
    {
        x = 2 * x + 1;
    }
    cout << x << endl;
}