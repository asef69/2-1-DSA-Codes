#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,m;
    cin>>n>>m;
    vector<vector<pair<long long,long long> > >adj(n+1);
    for(int i=0;i<m;i++){
        long long u,v,w;
        cin>>u>>v>>w;

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    long long totalWeight=0;
    priority_queue<pair<long long,long long>,vector<pair<long long,long long> >,greater<pair<long long,long long> > >pq;
    vector<bool>visited(n+1,false);

    pq.push({0,1});

    while(!pq.empty()){
        auto front=pq.top();
        pq.pop();

        long long parent_node=front.second;
        long long parent_weight=front.first;

        if(visited[parent_node]) continue;

        visited[parent_node]=true;
        totalWeight+=parent_weight;

        for(auto child:adj[parent_node]){
            long long child_node=child.first;
            long long child_weight=child.second;

            if(!visited[child_node]){
                pq.push({child_weight,child_node});
            }
        }
    }
    
    long long visited_count=0;
    for(int i=1;i<=n;i++){
        if(visited[i]) visited_count++;
    }
    
    if(visited_count==n){
        cout<<totalWeight<<endl;
    }else{
        cout<<-1<<endl;
    }
}