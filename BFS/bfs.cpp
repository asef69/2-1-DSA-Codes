#include <bits/stdc++.h>
using namespace std;
vector<int> adj_list[1005];
bool visited[1005];
void bfs(int source)
{
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while (!q.empty())
    {
        int parent = q.front();
        q.pop();
        cout << parent << " ";
        for (int children : adj_list[parent])
        {
            if (visited[children] == false)
            {
                q.push(children);
                visited[children] = true;
            } 
        }
    }
}
int main()
{
    int n, e;
    cin >> n >> e;

    while (e--)
    {
        int a, b;
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }
    memset(visited, false, sizeof(visited));
    bfs(0);
}