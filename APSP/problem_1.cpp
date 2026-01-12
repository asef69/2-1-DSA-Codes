/*
Problem Set 1: City Network Problems
P1.1: Directed City Network
Problem Statement:
You are given a network of n cities connected by m directed roads. Each road has a specific direction and length. You need to answer q queries where each query asks for the shortest distance between two cities a and b. If there is no path from a to b, output -1.

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

1 ≤ n ≤ 200

1 ≤ m ≤ n²

1 ≤ q ≤ 10⁴

1 ≤ a, b ≤ n

1 ≤ c ≤ 10⁶

All roads are directed (one-way)

Output Format:
For each query, output one integer: the shortest distance from city a to city b. If no path exists, output -1.

Example:

text
Input:
4 5 3
1 2 5
2 1 3
2 3 4
3 4 2
4 2 1
1 3
3 1
1 4

Output:
9
-1
11
Explanation:

1→3: 1→2(5) + 2→3(4) = 9

3→1: No path exists → -1

1→4: 1→2(5) + 2→3(4) + 3→4(2) = 11
*/

#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int main(){
    int n,m,q;
    cin>>n>>m>>q;

    vector<vector<long long> > dist(n+1,vector<long long>(n+1,INF));
    for(int i=1;i<=n;i++){
        dist[i][i]=0;
    }
    for(int i=1;i<=m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        if (dist[a][b] > c) {
            dist[a][b] = c;
        }
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(dist[k][j]!=INF && dist[i][k]!=INF)
                {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }

    for(int i=0;i<q;i++){
        int a,b;
        cin>>a>>b;
        if(dist[a][b]==INF) {
            cout<<-1<<endl;
        }
        else{
            cout<<dist[a][b]<<endl;
        }
    }
}