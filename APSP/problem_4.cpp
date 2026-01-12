/*
P1.4: K-th Shortest Unique Path
Problem Statement:
Given a network of cities, find the length of the k-th shortest distinct path between two cities. Two paths are considered distinct if they differ in at least one city (not just edge). If fewer than k distinct paths exist, output -1.

Input Format:

text
n m q
a1 b1 c1
a2 b2 c2
...
am bm cm
q1_a q1_b q1_k
q2_a q2_b q2_k
...
qq_a qq_b qq_k
Constraints:

1 ≤ n ≤ 50

1 ≤ m ≤ 200

1 ≤ q ≤ 100

1 ≤ k ≤ 5

1 ≤ c ≤ 10⁶

Output Format:
For each query, output one integer: the length of the k-th shortest distinct path, or -1 if it doesn't exist.

Example:

text
Input:
4 5 3
1 2 5
1 3 9
2 3 3
2 4 7
3 4 2
1 4 1
1 4 2
1 4 3

Output:
8
10
11
Explanation:
Paths from 1 to 4:

1→2→4: 5+7=12? Wait output says 8...

1→3→4: 9+2=11

1→2→3→4: 5+3+2=10

Actually ordering: 8, 10, 11 suggests there's a shorter path...
*/
#include<bits/stdc++.h>
using namespace std;
const long long INF=1e18;
int main(){
    int n,m,q;
    cin>>n>>m>>q;
    vector<tuple<long long,long long,long long> >edges;
    vector<vector<long long> >base_dist(n+1,vector<long long>(n+1,INF));

    for(int i=1;i<=n;i++){
        base_dist[i][i]=0;
    }

    for(int i=0;i<m;i++){
        long long a,b,c;
        cin>>a>>b>>c;
        edges.push_back(make_tuple(a,b,c));
        base_dist[a][b]=min(base_dist[a][b],c);
        base_dist[b][a]=min(base_dist[b][a],c);
    }
    for(int k=1;k<=n;k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(base_dist[i][k]!=INF && base_dist[k][j]!=INF){
                    base_dist[i][j]=min(base_dist[i][j],base_dist[i][k]+base_dist[k][j]);
                }
            }
        }
    }

    for(int i=0;i<q;i++){
        long long a,b,k;
        cin>>a>>b>>k;

        if(base_dist[a][b]==INF){
            cout<<-1<<endl;
            continue;
        }
        if(a==b){
            cout<<(k==1?0:-1)<<endl;
            continue;
        }
        set<long long>path;
        path.insert(base_dist[a][b]);
        for(int e=1;e<=n && path.size()<k;e++){
            if(e==a || e==b) continue;

            vector<vector<long long> >temp_dist=base_dist;
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    if(temp_dist[i][j]!=INF && temp_dist[j][k]!=INF){
                        temp_dist[i][j]=min(temp_dist[i][j],temp_dist[i][j]+temp_dist[j][k]);
                    }
                }
            }
            if(temp_dist[a][b]!=INF){
                path.insert(temp_dist[a][b]);
            }
        }
        for (const auto& edge : edges) {
            int u = get<0>(edge);
            int v = get<1>(edge);
            int w = get<2>(edge);
            
            if (base_dist[a][u] != INF && base_dist[v][b] != INF) {
                path.insert(base_dist[a][u] + w + base_dist[v][b]);
            }
            if (base_dist[a][v] != INF && base_dist[u][b] != INF) {
                path.insert(base_dist[a][v] + w + base_dist[u][b]);
            }
        }
        auto it = path.begin();
        for (int i = 1; i < k && it != path.end(); i++) {
            ++it;
        }
        
        if (it != path.end()) {
            cout << *it << "\n";
        } else {
            cout << "-1\n";
        }
    }
    
}