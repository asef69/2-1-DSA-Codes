#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;
int main()
{
    int t;
    cin>> t;
    int case_num = 1;
    while (t--)
    {
        long long N,M,F;
        cin>>N>>M>>F;

        vector<vector<long long> >dist(N+1,vector<long long>(N+1,INF));
        for(long long i=1;i<=N;i++){
            dist[i][i]=0;
        }

        for(long long i=0;i<M;i++){
            long long u,v,w;
            cin>>u>>v>>w;
            if(w<dist[u][v]){
                dist[u][v]=w;
                dist[v][u]=w;
            }
        }
        vector<long long> friends(F);
        map<long long,long long> friend_indx;

        for(long long i=0;i<F;i++){
            cin>>friends[i];
            friend_indx[friends[i]]=i;
        }
        for (long long k = 1; k <= N; k++) {
            for (long long i = 1; i <= N; i++) {
                if (dist[i][k] == INF) continue;
                for (long long j = 1; j <= N; j++) {
                    if (dist[k][j] == INF) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
        long long ans=INF;
        sort(friends.begin(),friends.end());
        do{
            long long total=0;
            long long current=1;
            for(long long i=0;i<F;i++){
                total+=dist[current][friends[i]];
                current=friends[i];
            }

            total+=dist[current][N];
            ans=min(total,ans);
        }while(next_permutation(friends.begin(),friends.end()));

        cout << "Case " << case_num << ": " << ans << "\n";
        case_num++;
    }
}