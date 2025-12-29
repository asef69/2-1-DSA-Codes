#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> adj(n);
    vector<int>indegree(n,0);

    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        indegree[v]++;
    }

    queue<int>q;
    for(int i=0;i<n;i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    int visited=0;
    while(!q.empty()){
        int node=q.front();
        q.pop();
        visited++;

        for(int neighbour:adj[node]){
            indegree[neighbour]--;
            if(indegree[neighbour]==0){
                q.push(neighbour);
            }
        }
    }
    if(visited==n){
        cout<<"Yes"<<endl;
    }
    else cout<<"No"<<endl;
}