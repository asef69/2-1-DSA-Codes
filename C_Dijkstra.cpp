#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m;
    cin>>n>>m;
    vector<vector<tuple<long long,long long,long long>>> adj_list(n+1);
    vector<tuple<long long,long long,long long>> edges(m);

    for(long long i=0;i<m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        adj_list[a].push_back(make_tuple(b,c,i));
        adj_list[b].push_back(make_tuple(a,c,i));
        edges[i]=make_tuple(a,b,c);
    }

    vector<long long>dist(n+1,LLONG_MAX);
    vector<long long>prev_vertex(n+1,-1);
    vector<long long>prev_edge(n+1,-1);

    dist[1]=0;
    priority_queue<pair<long long,long long>,vector<pair<long long,long long>>,greater<pair<long long,long long>>>pq;
    pq.push({0,1});
    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();

        auto parent_node=front.second;
        auto parent_weight=front.first;

        if(parent_weight>dist[parent_node]) continue;

        for(auto edge:adj_list[parent_node]){
            auto node=get<0>(edge);
            auto weight=get<1>(edge);
            auto index=get<2>(edge);

            if(parent_weight+weight<dist[node]){
                dist[node]=parent_weight+weight;
                pq.push({dist[node],node});
                prev_vertex[node]=parent_node;
                prev_edge[node]=index;
            }
        }
    }

    if(dist[n]==LLONG_MAX){
        cout<<-1<<endl;
        return 0;
    }
    
    vector<long long>path;
    long long current=n;
    while(current!=1){
        path.push_back(current);
        current=prev_vertex[current];
    }
    path.push_back(1);
    reverse(path.begin(),path.end());
    
    for(auto vertex:path){
        cout<<vertex<<" ";
    }

    return 0;
}
