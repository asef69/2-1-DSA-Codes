#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n) {
        p.resize(n);
        r.assign(n, 0);
        for (int i = 0; i < n; i++) p[i] = i;
    }
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
};
int main() {
    int N, M, R, K;
    cin >> N >> M;
    vector<vector<pair<int,int>>> g(N);
    for (int i = 0; i < M; i++) {
        int u,v,w; cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    cin >> R >> K;

    vector<int> vis(N, 0);
    priority_queue<tuple<int,int,int>,
        vector<tuple<int,int,int>>,
        greater<>> pq;

    pq.push(make_tuple(0, R, -1));
    long long cost = 0;
    int rootDeg = 0, taken = 0;

    while (!pq.empty()) {
        auto [w,u,p] = pq.top(); pq.pop();
        if (vis[u]) continue;
        if (p == R && rootDeg == K) continue;

        vis[u] = 1;
        cost += w;
        taken++;

        if (p == R) rootDeg++;

        for (auto [v,wt] : g[u])
            if (!vis[v]) pq.push(make_tuple(wt, v, u));
    }

    if (taken != N || rootDeg != K) cout << "Impossible\n";
    else cout << cost << "\n";
}
