#include<bits/stdc++.h>
using namespace std;
char grid[105][105];
bool visited[105][105];
vector<pair<int,int>>directions={{-1,0},{1,0},{0,-1},{0,1}};
int n,m;
bool valid(int i,int j){
    if(i<0 || i>=n || j<0 || j>=m) return false;
    return true;
}
void bfs(int sx,int sy){
    queue<pair<int,int>>q;
    q.push({sx,sy});
    visited[sx][sy]=true;
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();
        cout<<x<<" "<<y<<endl;
        for(int i=0;i<4;i++){
            int nx=x+directions[i].first;
            int ny=y+directions[i].second;
            if(valid(nx,ny) && !visited[nx][ny]){
                visited[nx][ny]=true;
                q.push({nx,ny});
            }
        }
    }
}
int main(){
    
    cin>>n>>m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>grid[i][j];
        }
    }
    memset(visited,false,sizeof(visited));
    int si,sj;
    cin>>si>>sj;
    bfs(si,sj);
}