#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int main(){
    int N,M,F;
    cin>>N>>M>>F;
    vector<int>capacity(N+1);
    for(int i=1;i<=N;i++){
        cin>>capacity[i];
    }
    vector<vector<pair<int,int>>> adj_list(N+1);
    for(int i=0;i<M;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj_list[u].push_back(make_pair(v,w));
        adj_list[v].push_back(make_pair(u,w));
    }
    int K;
    cin>>K;

    vector<long long>dist(N+1,INF);
    dist[1]=0;
    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
    pq.push(make_pair(0,1));
    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();

        long long distance=front.first;
        int node=front.second;
        if(distance>dist[node]) continue;

        for(auto child:adj_list[node]){
            int child_node=child.first;
            int child_weight=child.second;

            if(child_weight+dist[node]<dist[child_node]){
                dist[child_node]=child_weight+dist[node];
                pq.push(make_pair(dist[child_node],child_node));
            }
        }
    }

    set<pair<long long,int>> available;

    for(int i=1;i<=N;i++){
        if(capacity[i]>0){
            available.insert(make_pair(dist[i],i));
        }
    }
    for(int student=0;student<K;student++){
        if(available.empty()){
            cout<<-1<<endl;
            continue;
        }
        long long d;
        int lab;
        tie(d,lab)=*available.begin();

        long long cost=d+F;
        cout<<cost<<" ";
        capacity[lab]--;
        if(capacity[lab]==0){
            available.erase(available.begin());
        }
    }
    cout<<endl;
}