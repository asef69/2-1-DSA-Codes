#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    map<string, int> mp;
    int roll = 0;
    for (int i = 0; i < n; i++)
    {
        string name;
        cin >> name;
        if (mp.find(name) != mp.end())
        {
            cout << mp[name] << endl;
        }
        else
        {
            mp[name] = roll;
            roll++;
        }
    }
}