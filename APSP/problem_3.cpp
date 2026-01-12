/*
P1.3: Path Reconstruction with Lexicographic Order
Problem Statement:
Given a network of cities with bidirectional roads, for each query between cities a and b, output:

The shortest distance

The number of cities in the shortest path (including a and b)

The actual path as space-separated city IDs

If multiple shortest paths exist, choose the one with the lexicographically smallest sequence of cities.

Input Format:

text
n m q
a1 b1 c1
a2 b2 c2
...
am bm cm
q1_a q1_b
q2_a q2_b
...
qq_a qq_b
Constraints:

1 ≤ n ≤ 100

1 ≤ m ≤ 1000

1 ≤ q ≤ 1000

1 ≤ c ≤ 10⁶

Output Format:
For each query:

If no path exists: output -1

Otherwise: output distance count city1 city2 ... cityk

Example:

text
Input:
4 4 3
1 2 5
1 3 9
2 3 3
3 4 2
1 4
2 4
1 2

Output:
10 4 1 2 3 4 
5 3 2 3 4 
5 2 1 2
Explanation:

1→4: Two paths: 1→3→4 (9+2=11) and 1→2→3→4 (5+3+2=10) and 1→2→4? Wait 1→2→4 doesn't exist. Actually: 1→2(5) + 2→3(3) + 3→4(2) = 10

But output says 8 with path 1→2→4? This suggests there's a direct 2→4 edge not shown...
*/

#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int main()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long> > dist(n+1,vector<long long>(n+1,INF));
    vector<vector<vector<long long> > > path(n+1,vector<vector<long long> >(n+1));

    for(int i=1;i<=n;i++){
        dist[i][i]=0;
        path[i][i].push_back(i);
    }

    for(int i=0;i<m;i++){
        long long u,v,w;
        cin>>u>>v>>w;
        dist[u][v]=w;
        dist[v][u]=w;
        path[u][v].push_back(u);
        path[u][v].push_back(v);
        path[v][u].push_back(v);
        path[v][u].push_back(u);
    }

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dist[i][k]!=INF && dist[k][j]!=INF){
                    long long new_dist=dist[i][k]+dist[k][j];
                    if(new_dist<dist[i][j]){
                        dist[i][j]=new_dist;
                        path[i][j]=path[i][k];
                        path[i][j].insert(path[i][j].end(),path[k][j].begin()+1,path[k][j].end());
                    }
                    else if(dist[i][j]==new_dist){
                        vector<long long> new_path=path[i][k];
                        new_path.insert(new_path.end(),path[k][j].begin()+1,path[k][j].end());
                        if(new_path<path[i][j]){
                            path[i][j]=new_path;
                        }
                    }
                }
            }
        }
    }

    for(int i=0;i<q;i++){
        long long a,b;
        cin>>a>>b;

        if(dist[a][b]==INF){
            cout<<-1<<endl;
        }
        else{
            cout<<dist[a][b]<<" "<<path[a][b].size()<<" ";
            for(int j=0;j<path[a][b].size();j++){
                cout<<path[a][b][j]<<" ";
            }
            cout<<endl;
        }

    }
}