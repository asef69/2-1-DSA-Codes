#include <bits/stdc++.h>
using namespace std;

/* ---------- DSU ---------- */
struct DSU {
    vector<int> parent, rankv;

    DSU(int n) {
        parent.resize(n);
        rankv.assign(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false;

        if (rankv[a] < rankv[b]) swap(a, b);
        parent[b] = a;
        if (rankv[a] == rankv[b]) rankv[a]++;
        return true;
    }
};

/* ---------- EDGE ---------- */
struct Edge {
    int u, v;
    long long w;
    bool inMST = false;
};

vector<vector<pair<int,long long>>> tree;

bool dfs(int u, int t, int p, long long &mx) {
    if (u == t) return true;
    for (auto [v,w] : tree[u]) {
        if (v == p) continue;
        long long prev = mx;
        mx = max(mx, w);
        if (dfs(v, t, u, mx)) return true;
        mx = prev;
    }
    return false;
}

int main() {
    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a.w < b.w; });

    DSU dsu(N);
    long long mstCost = 0;
    tree.assign(N, {});

    vector<bool> used(M,false);

    for (int i = 0; i < M; i++) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            mstCost += edges[i].w;
            used[i] = true;
            tree[edges[i].u].push_back({edges[i].v, edges[i].w});
            tree[edges[i].v].push_back({edges[i].u, edges[i].w});
        }
    }

    long long second = LLONG_MAX;
    for (int i = 0; i < M; i++) {
        if (used[i]) continue;
        long long mx = 0;
        dfs(edges[i].u, edges[i].v, -1, mx);
        second = min(second, mstCost + edges[i].w - mx);
    }

    cout << mstCost << "\n";
    if (second == LLONG_MAX) cout << -1 << "\n";
    else cout << second << "\n";
}
