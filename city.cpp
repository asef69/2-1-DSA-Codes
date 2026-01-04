#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int main(){
    int N,M;
    cin>>N>>M;
    vector<int>tax(N+1);
    for(int i=1;i<=N;i++){
        cin>>tax[i];
    }
    vector<vector<int>> graph(N+1);
    for(int i=1;i<=M;i++){
        int u,v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    vector<long long>dist(N+1,INF);

    dist[1]=0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    pq.push(make_pair(0,1));

    while(!pq.empty()){
        long long cost;
        int u;
        tie(cost,u)=pq.top();
        pq.pop();
        if(cost>dist[u]) continue;

        for(auto v:graph[u]){
            long long newCost=dist[u]+tax[v];

            if(newCost<dist[v]){
                dist[v]=newCost;
                pq.push(make_pair(dist[v],v));
            }
        }
    }
    cout<<dist[N]<<endl;
}