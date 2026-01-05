#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
class Edge{
    public:
    int to,time,cost;
    Edge(int to,int time,int cost){
        this->to=to;
        this->time=time;
        this->cost=cost;
    }
};
int main(){
int K,N,X;
cin>>K>>N>>X;
vector<vector<Edge>> graph(N+1);
for(int i=0;i<X;i++){
    int u,v,time,cost;
    cin>>u>>v>>time>>cost;
    graph[u].push_back(Edge(v,time,cost));
    graph[v].push_back(Edge(u,time,cost));
}
int S,D;
cin>>S>>D;
vector<long long>dist(N+1,INF);
vector<int>prev_vertex(N+1,-1);
vector<long long>totalTime(N+1,INF);

priority_queue<tuple<long long,long long,int>,vector<tuple<long long,long long,int>>,greater<tuple<long long,long long,int>>> pq;
dist[S]=0,totalTime[S]=0;
pq.push(make_tuple(0,0,S));

while(!pq.empty()){
    auto front=pq.top();
    pq.pop();

    long long cost=get<0>(front);
    long long time=get<1>(front);
    int node=get<2>(front);

    if(cost>dist[node]) continue;

    for(auto edge:graph[node]){
        int child_node=edge.to;
        long long new_cost,new_time;

        if(node==S){
            new_cost=cost+edge.cost+K*edge.time;
            new_time=time+edge.time;
        }
        else{
            new_cost=cost+edge.cost+K*(edge.time+1);
            new_time=time+edge.time+1;
        }

        if(dist[child_node]>new_cost){
            dist[child_node]=new_cost;
            prev_vertex[child_node]=node;
            totalTime[child_node]=new_time;
            pq.push(make_tuple(new_cost,new_time,child_node));
        }
    }
}

if(dist[D]==INF){
    cout<<"error"<<endl;
    return 0;
}
vector<int>path;
int current=D;
while(current!=-1){
    path.push_back(current);
    current=prev_vertex[current];
}
reverse(path.begin(),path.end());

for(int i=0;i<path.size();i++){
    if(i>0) cout<<"->";
    cout<<path[i];
}
cout<<" "<<totalTime[D]<<" "<<dist[D]<<endl;

}