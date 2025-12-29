#include<bits/stdc++.h>
using namespace std;
long long n,m,s,t;

int main(){
    cin>>n>>m>>s>>t;
    vector<tuple<long long,long long,long long>> adj_list[n];
    vector<tuple<long long,long long,long long>> edges(m);

    for(long long i=0;i<m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        adj_list[a].push_back(make_tuple(b,c,i));
        edges[i]=make_tuple(a,b,c);
    }
    vector<long long> dist(n,LLONG_MAX);
    vector<long long> prev_vertex(n,-1);
    vector<long long> prev_edge(n,-1);

    dist[s]=0;
    priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>> pq;
    pq.push({0,s});
    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();

        if(front.first>dist[front.second]) continue;

        for(auto edge:adj_list[front.second]){
            auto node=get<0>(edge);
            auto weight=get<1>(edge);
            auto index=get<2>(edge);

            if(front.first+weight<dist[node]){
                dist[node]=front.first+weight;
                pq.push({dist[node],node});
                prev_vertex[node]=front.second;
                prev_edge[node]=index;
            }
        }
    }
    if(dist[t]==LLONG_MAX){
        cout<<"-1"<<endl;
        return 0;
    }
    vector<long long>path;
    long long current=t;
    while(current!=s){
        path.push_back(prev_edge[current]);
        current=prev_vertex[current];
    }
    reverse(path.begin(),path.end());

    cout<<dist[t]<<" "<<path.size()<<endl;

    for(auto edge_id:path){
        cout<<get<0>(edges[edge_id])<<" "<<get<1>(edges[edge_id])<<endl;
    }
}
