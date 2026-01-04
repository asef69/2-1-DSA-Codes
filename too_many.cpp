#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main()
{
    int N, M, F;
    cin >> N >> M >> F;

    vector<int> capacity(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> capacity[i];
    }
    vector<vector<pair<int, int>>> graph(N + 1);
    for (int i = 0; i < M; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }
    vector<long long> dist(N + 1, INF);
    dist[1] = 0;
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    pq.push(make_pair(0, 1));
    while (!pq.empty())
    {
        long long d;
        int u;
        tie(d, u) = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;

            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    set<pair<long long, int>> available;
    for (int i = 1; i <= N; i++)
    {
        if (capacity[i] > 0)
            available.insert(make_pair(dist[i], i));
    }
    int K;
    cin >> K;

    for (int student = 0; student < K; student++)
    {
        if (available.empty())
        {
            cout << -1 << " ";
            continue;
        }

        long long d;
        int lab;
        tie(d, lab) = *available.begin();

        long long cost = d + F;
        cout << cost << " ";

        capacity[lab]--;
        if (capacity[lab] == 0)
            available.erase(available.begin());
    }
    cout << endl;
    return 0;
}