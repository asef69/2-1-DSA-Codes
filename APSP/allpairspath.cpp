#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e18;

int main()
{
    int n, m, q;
    while (cin >> n >> m >> q)
    {
        if (n == 0 && m == 0 && q == 0)
            break;

        vector<vector<long long> > dist(n, vector<long long>(n, INF));
        vector<vector<bool> > visited(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++)
        {
            dist[i][i] = 0;
            visited[i][i] = true;
        }
        for (int i = 0; i < m; i++)
        {
            int u, v;
            long long w;
            cin >> u >> v >> w;
            if (w < dist[u][v])
            {
                dist[u][v] = w;
                visited[u][v] = true;
            }
        }

        for (int k = 0; k < n; k++)
        {
            for (int i = 0; i < n; i++)
            {
                if (dist[i][k] == INF)
                    continue;
                for (int j = 0; j < n; j++)
                {
                    if (dist[k][j] == INF)
                        continue;
                    if (dist[i][j] > dist[i][k] + dist[k][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        visited[i][j] = visited[i][k] && visited[k][j];
                    }
                }
            }
        }
        vector<bool> neg_cycle(n,false);
        for(int i=0;i<n;i++){
            if(dist[i][i]<0){
                neg_cycle[i]=true;
            }
        }

        vector<vector<bool> >affected_neg_cycle(n,vector<bool>(n,false));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(!visited[i][j]) continue;
                for(int k=0;k<n;k++){
                    if(visited[i][k] && neg_cycle[k] && visited[k][j]){
                        affected_neg_cycle[i][j]=true;
                        break;
                    }
                }
            }
        }

        for(int i=0;i<q;i++){
            int u,v;
            cin>>u>>v;

            if(!visited[u][v]){
                cout<<"Impossible"<<endl;
            }
            else if (affected_neg_cycle[u][v])
            {
                cout<<"-Infinity"<<endl;
            }
            else{
                cout<<dist[u][v]<<endl;
            }
        }
        cout<<endl;
    }
}