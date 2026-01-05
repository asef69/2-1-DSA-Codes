#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int main(){
    int n,m,k,b,e;
    cin>>n>>m>>k>>b>>e;
    vector<int>capitals(k);
    for(int i=0;i<k;i++){
        cin>>capitals[i];
    }
    vector<bool>blocked_cities(n+1,false);
    for(int i=0;i<b;i++){
        int a; cin>>a;
        blocked_cities[a]=true;
    }
    vector<int>emergency(e);
    for(int i=0;i<e;i++){
        cin>>emergency[i];
    }
    vector<vector<pair<int,long long>>> graph(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        long long w;
        cin>>u>>v>>w;
        if(!blocked_cities[u] && !blocked_cities[v]){
            graph[u].push_back(make_pair(v,w));
        }
    }
    vector<long long> dist(n+1,INF);
    dist[0]=0;

    for(int cap:capitals){
        if(!blocked_cities[cap]){
            graph[0].push_back(make_pair(cap,0));
        }
    }

    for(int i=0;i<n;i++){
        bool updated=false;
        for(int u=0;u<=n;u++){
            if(dist[u]==INF) continue;
            for(auto child:graph[u]){
                int child_node=child.first;
                long long child_weight=child.second;
                if(dist[u]+child_weight<dist[child_node]){
                    dist[child_node]=dist[u]+child_weight;
                    updated=true;
                }
            }
        }
        if(!updated) break;
    }

    for(int i=0;i<=n;i++){
        if(dist[i]==INF) continue;
        for(auto child:graph[i]){
            int node=child.first;
            long long weight=child.second;

            if(dist[i]+weight<dist[node]){
                cout<<"Abyss Detected"<<endl;
                return 0;
            }
        }
    }
    for(int target:emergency){
        if(blocked_cities[target]||dist[target]==INF){
            cout<<"INF"<<endl;
        }
        else{
            cout<<dist[target]<<endl;
        }
    }

}