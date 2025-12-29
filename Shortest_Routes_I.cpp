#include<bits/stdc++.h>
using namespace std;
long long n,m;
vector<pair<long long,long long>> adj_list[100005];
long long dist[100005];
bool visited[100005];

void dijkstra(long long source){
    priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>>pq;
    pq.push({0,source});
    while(!pq.empty()){
        pair<long long,long long> front=pq.top();
        pq.pop();

        long long weight=front.first;
        long long node=front.second;
        
        if(visited[node]) continue;
        visited[node]=true;
        
        for(auto child: adj_list[node]){
            long long child_node=child.second;
            long long child_cost=child.first;
            if(child_cost+weight<dist[child_node]){
                dist[child_node]=child_cost+weight;
                pq.push({dist[child_node],child_node});
            }
        }
    }
}

int main(){
    cin>>n>>m;
    for(long long i=1;i<=m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        adj_list[a].push_back({c,b});
    }
    for(long long i=1;i<=n;i++){
        dist[i]=LLONG_MAX;
    }
    dist[1]=0;
    dijkstra(1);
    for(long long i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    }
}
