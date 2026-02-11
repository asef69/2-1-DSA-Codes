#include <bits/stdc++.h>
using namespace std;

int main()
{
    long long n;
    cin >> n;
    vector<long long> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    sort(arr.begin(), arr.end());

    long long q;
    cin >> q;

    multiset<long long> ms(arr.begin(), arr.end());

    for (int i = 0; i < q; i++)
    {
        long long operation;
        cin >> operation;

        if (operation == 1)
        {
            auto max_it = prev(ms.end());
            long long max_val = *max_it;
            ms.erase(max_it);

            long long new_val;
            if (max_val >= 0)
            {
                new_val = max_val / 2;
            }
            else
            {
                new_val = (max_val - 1) / 2;
            }

            ms.insert(new_val);
        }
        else
        {
            auto min_it = ms.begin();
            long long min_val = *min_it;
            ms.erase(min_it);

            if (min_val > LLONG_MAX / 2)
            {
                min_val = LLONG_MAX;
            }
            else
            {
                min_val *= 2;
            }

            ms.insert(min_val);
        }
    }

    long long result = 0;
    for (auto val : ms)
    {
        result += val;
    }

    cout << result << endl;

    return 0;
}