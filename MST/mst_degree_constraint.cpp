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
    int N, M;
    cin >> N >> M;
    vector<int> lim(N);
    for (int &x : lim) cin >> x;

    vector<Edge> edges(M);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a.w < b.w; });

    vector<int> deg(N, 0);
    DSU dsu(N);
    long long cost = 0;
    int cnt = 0;

    for (auto &e : edges) {
        if (deg[e.u] == lim[e.u] || deg[e.v] == lim[e.v]) continue;
        if (dsu.unite(e.u, e.v)) {
            deg[e.u]++; deg[e.v]++;
            cost += e.w;
            cnt++;
        }
    }

    if (cnt != N - 1) cout << -1 << "\n";
    else cout << cost << "\n";
}
