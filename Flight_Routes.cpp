#include<bits/stdc++.h>
using namespace std;
long long n,m,k;
vector<pair<long long,long long>> adj_list[100005];
long long dist[100005];
void bfs(int start,int end){
    
}
int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        adj_list[a].push_back({b,c});
    }
    for(int i=1;i<=n;i++){
        dist[i]=LLONG_MAX;
    }
    bfs(1,n);

}