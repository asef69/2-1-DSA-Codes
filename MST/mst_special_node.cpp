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
    int N, M, X;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;
    cin >> X;

    DSU dsu(N);
    long long cost = 0;
    int cnt = 0;

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a.w < b.w; });

    for (auto &e : edges) {
        if (e.u != X && e.v != X) continue;
        if (dsu.unite(e.u, e.v)) {
            cost += e.w;
            cnt++;
        }
    }

    if (cnt != N - 1) cout << -1 << "\n";
    else cout << cost << "\n";
}
