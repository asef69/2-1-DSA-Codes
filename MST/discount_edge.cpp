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
    vector<Edge> edges(M);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a.w < b.w; });

    DSU dsu(N);
    vector<Edge> mst;
    long long mstCost = 0;

    for (auto &e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            mstCost += e.w;
        }
    }

    long long ans = mstCost;
    for (auto &e : mst)
        ans = min(ans, mstCost - e.w + e.w / 2);

    cout << ans << "\n";
}
