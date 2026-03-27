#include <bits/stdc++.h>
using namespace std;
const long long N = 1e6 + 5;
long long a[N];
int main() {
    long long t, n, m, i;
    long long k;
    cin>>t;
    while(t--){
        cin>>n;
        m=0;
        for(int i=0;i<n;i++){
            cin>>a[i];
            if(a[i]>a[m]){
                m=i;
            }
        }
        a[n]=a[0];
        k=-a[m];
        for(int i=0;i<n;i++){
            k+=max(a[i],a[i+1]);
        }
        cout<<k<<endl;
    }

}