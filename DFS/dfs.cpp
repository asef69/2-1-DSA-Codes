#include<bits/stdc++.h>
using namespace std;
vector<int>adj_list[1005];
bool visited[1005];
void dfs(int source){
    cout<<source<<" ";
    visited[source]=true;
    for(int child:adj_list[source]){
        if(!visited[child]){
            dfs(child);
        }
    }
}
int main(){
    int n,e;
    cin>>n>>e;
    while(e--){
        int a,b;
        cin>>a>>b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);

    }
    memset(visited,false,sizeof(visited));
    dfs(0);
}