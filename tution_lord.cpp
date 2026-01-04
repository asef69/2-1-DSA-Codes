#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
struct Edge{
public:
int to,t,c;
Edge(int to,int t, int c){
    this->to=to;
    this->t=t;
    this->c=c;
}
};
int main(){
    long long K;
    int N,X;
    cin>>K>>N>>X;
    vector<vector<Edge>> graph(N+1);
    for(int i=0;i<X;i++){
        int u,v,t,c;
        cin>>u>>v>>t>>c;
        graph[u].push_back(Edge(v,t,c));
        graph[v].push_back(Edge(u,t,c));
    }
    int S,D;
    cin>>S>>D;

    vector<long long>dist(N+1,INF);
    vector<long long>totalTime(N+1,INF);
    vector<int>prev_vertex(N+1,-1);

    priority_queue<tuple<long long,long long,int>,vector<tuple<long long, long long, int>>,greater<tuple<long long, long long,int>>> pq;

    dist[S]=0;
    totalTime[S]=0;
    pq.push(make_tuple(0,0,S));

    while(!pq.empty()){
        long long cost, time;
        int u;
        tie(cost,time,u)=pq.top();
        pq.pop();

        if(cost>dist[u]) continue;

        for(auto edge:graph[u]){
            int v=edge.to;
            long long new_time,new_cost;

            if(u==S){
                new_time=time+edge.t;
                new_cost=cost+edge.c+K*edge.t;
            }
            else{
                new_time=time+edge.t+1;
                new_cost=cost+edge.c+K*(edge.t+1);
            }

            if(new_cost<dist[v]){
                dist[v]=new_cost;
                totalTime[v]=new_time;
                prev_vertex[v]=u;
                pq.push(make_tuple(dist[v],totalTime[v],v));
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

    for(size_t i=0;i<path.size();i++){
        if(i>0) cout<<"->";
        cout<<path[i];
    }
    cout<<" "<<totalTime[D]<<" "<<dist[D]<<endl;


}