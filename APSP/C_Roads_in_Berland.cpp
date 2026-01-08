#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;

int main(){
    long long n;
    cin>>n;
    vector<vector<long long> > dist(n, vector<long long>(n));
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>dist[i][j];
        }
    }
    long long k;
    cin>>k;
    while(k--){
        long long a,b,c,ans=0;
        cin>>a>>b>>c;
        a--; b--;
        dist[a][b]=dist[b][a]=min(dist[a][b],c);

        for(int k=0;k<n;k++){
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                ans+=dist[i][j];
            }
        }
        cout<<ans<<" ";
    }

    return 0;
}