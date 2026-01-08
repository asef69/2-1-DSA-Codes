#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int main(){
    int n;
    cin>>n;
    map<string,int>currency_index;
    vector<string>currency(n);
    for(int i=0;i<n;i++){
        cin>>currency[i];
        currency_index[currency[i]]=i;
    }
    vector<vector<double> > dist(n,vector<double>(n,INF));

    for(int i=0;i<n;i++){
        dist[i][i]=0;
    }

    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        string from,to;
        double rate;
        cin>>from>>rate>>to;

        int u=currency_index[from];
        int v=currency_index[to];

        dist[u][v]=min(dist[u][v],-log(rate));

    }

    for(int k=0;k<n;k++){
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(dist[i][k]!=INF && dist[k][j]!=INF){
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }
    bool arbitrage=false;
    for(int i=0;i<n;i++){
        if(dist[i][i]<0){
            arbitrage=true;
            break;
        }
    }
    if(arbitrage) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
}