/*
P1.2: Shortest Path with Forbidden City
Problem Statement:
You are given a network of n cities connected by m bidirectional roads. For each query, you need to find the shortest path between cities a and b that does not pass through a forbidden city f. The forbidden city cannot be used as an intermediate city in the path (but can be start or end if specified in query).

Input Format:

text
n m q
a1 b1 c1
a2 b2 c2
...
am bm cm
q1_a q1_b q1_f
q2_a q2_b q2_f
...
qq_a qq_b qq_f
Constraints:

1 ≤ n ≤ 100

1 ≤ m ≤ n(n-1)/2

1 ≤ q ≤ 10³

1 ≤ a, b, f ≤ n

1 ≤ c ≤ 10⁶

All roads are bidirectional

Output Format:
For each query, output one integer: the shortest distance avoiding city f. If no such path exists, output -1.

Example:

text
Input:
5 6 4
1 2 5
1 3 9
2 3 3
2 4 7
3 4 2
4 5 4
1 4 3
1 5 2
2 5 4
3 5 3

Output:
12
15
-1
-1
Explanation:

Query 1: 1→4 avoiding city 3: 1→2(5) + 2→4(7) = 12

Query 2: 1→5 avoiding city 2: 1→3(9) + 3→4(2) + 4→5(4) = 15, but actually 1→3(9) + 3→4(2) + 4→5(4) = 15, wait recalc... Actually: 1→3→4→5 = 9+2+4=15, but maybe there's shorter?

Query 3: 2→5 avoiding city 4: 2→3(3) + 3→? Need to check...
*/

#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<long long> >base_dist(n+1,vector<long long>(n+1,INF));

    for(int i=1;i<=n;i++){
        base_dist[i][i]=0;
    }

    for(int i=0;i<m;i++){
        long long  u,v,w;
        cin>>u>>v>>w;
        base_dist[u][v]=min(base_dist[u][v],w);
        base_dist[v][u]=min(base_dist[v][u],w);
    }
    
    vector<vector<long long> >full_dist=base_dist;

    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(full_dist[i][k]!=INF && full_dist[k][j]!=INF){
                    full_dist[i][j]=min(full_dist[i][j],full_dist[i][k]+full_dist[k][j]);
                }
            }
        }
    }

    for(int i=0;i<q;i++){
        long long a,b,f;
        cin>>a>>b>>f;

        if(a==f || b==f){
            if(a==f && b==f){
                cout<<0<<endl;
            }
            else{
                cout<<-1<<endl;
            }
            continue;
        }

        vector<vector<long long> > dist = base_dist;

        for(int k=1;k<=n;k++){
            if(k==f) continue;
            for(int i=1;i<=n;i++){
                for(int j=1;j<=n;j++){
                    if(dist[i][k]!=INF && dist[k][j]!=INF){
                        dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                    }
                }
            }
        }

        cout<<(dist[a][b]==INF?-1:dist[a][b])<<endl;
    }

    
}
