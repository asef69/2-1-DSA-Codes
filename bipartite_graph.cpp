#include <bits/stdc++.h>
using namespace std;

bool isBipartite(int vertices, vector<vector<int> > &graph)
{
    vector<int> color(vertices + 1, -1);

    for (int start = 0; start < vertices; start++)
    {
        if (color[start] == -1)
        {
            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty())
            {
                int node = q.front();
                q.pop();

                for (int neighbour : graph[node])
                {
                    if (color[neighbour] == -1)
                    {
                        color[neighbour] = 1 - color[node];
                        q.push(neighbour);
                    }
                    else if (color[neighbour] == color[node])
                    {
                        return false; 
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    int v, e;
    cin >> v >> e;

    vector<vector<int> > adj(v + 1);

    while (e--)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    if (isBipartite(v, adj))
        cout << "Bipartite" << endl;
    else
        cout << "Not Bipartite" << endl;

    return 0;
}
