#include <bits/stdc++.h>
#define ll long long int
using namespace std;

ll solve(vector<ll>& arr, ll X, ll N)
{
    map<ll, ll> prefSums;

    prefSums[0] = 1;
    ll pref = 0;
    ll cnt = 0;
    for (int i = 0; i < N; ++i) {
        pref += arr[i];
        cnt += (prefSums[pref - X]);
        prefSums[pref] += 1;
    }
    return cnt;
}

int main()
{

    ll N,X;
    cin>>N>>X;
    vector<ll>arr(N);
    for(ll i=0;i<N;i++){
        cin>>arr[i];
    }

    cout << solve(arr, X, N);
    return 0;
}