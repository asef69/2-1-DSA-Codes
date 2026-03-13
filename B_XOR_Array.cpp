#include<bits/stdc++.h>
using namespace std;

int main(){

    int t;
    cin>>t;
    while(t--){
        int n,l,r;
        cin>>n>>l>>r;

        long long prev_prefix = 0;
        for(int i=1;i<=n;i++){
            long long cur_prefix = (i==r ? (long long)(l-1) : (long long)i);
            long long val = prev_prefix ^ cur_prefix;
            cout<<val<<(i==n?'\n':' ');
            prev_prefix = cur_prefix;
        }
    }
}