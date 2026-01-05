#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m,k;
    cin>>n>>m>>k;
    vector<vector<pair<long long,long long>>> adj(n+1);

    for(long long i=0;i<m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
    }

    priority_queue<pair<long long,long long>> pq;
    vector<long long> vis(n+1,0);

    pq.push({0,1});

    while(!pq.empty() && vis[n]<k){
        auto node=pq.top().second;
        auto distance=pq.top().first;
        pq.pop();
        
        vis[node]++;
        
        if(node==n){
            cout<<-distance<<" ";
        }
        
        if(vis[node]<=k){
            for(auto edge:adj[node]){
                auto child_node=edge.first;
                auto child_weight=edge.second;
                pq.push({distance-child_weight,child_node});
            }
        }
    }
    cout<<endl;
}
