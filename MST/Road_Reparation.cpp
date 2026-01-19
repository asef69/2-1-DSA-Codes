#include<bits/stdc++.h>
using namespace std;
void prims(vector<vector<pair<long long, long long> > >&adj,vector<bool>&visited,long long n,long long root){
    priority_queue<pair<long long,long long>,vector<pair<long long,long long> >,greater<pair<long long,long long> > >pq;
    pq.push({0,root});
    long long totalWeight=0;
    long long count=0;
    
    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();

        long long parent_node=front.second;
        long long parent_weight=front.first;

        if(visited[parent_node]) continue;

        visited[parent_node]=true;
        count++;
        totalWeight+=parent_weight;

        for(auto child:adj[parent_node]){
            long long child_node=child.first;
            long long child_weight=child.second;

            if(!visited[child_node]){
                pq.push({child_weight, child_node});
            }
        }
    }
    
    if(count==n){
        cout<<totalWeight<<endl;
    } else {
        cout<<"IMPOSSIBLE"<<endl;
    }
}
int main(){
    long long n,m;
    cin>>n>>m;
    vector<vector<pair<long long, long long> > >adj(n+1);
    vector<bool>visited(n+1,false);

    for(long long i=0;i<m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back(make_pair(b,c));
        adj[b].push_back(make_pair(a,c));
    }

    prims(adj,visited,n,1);
}