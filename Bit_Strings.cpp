#include <bits/stdc++.h>
using namespace std;
const long long modulo = 1e9 + 7;

long long modExp(long long base, long long exp)
{
    long long result = 1;
    base = base % modulo;

    while (exp > 0)
    {
        if (exp % 2 == 1)
        {
            result = (result * base) % modulo;
        }
        exp = exp >> 1;
        base = (base * base) % modulo;
    }
    return result;
}
int main()
{
    long long n;
    cin >> n;
    long long result = modExp(2, n);
    cout << result << endl;
}