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

    int K;
    cin >> K;
    vector<Edge> cand(K);
    for (auto &e : cand) cin >> e.u >> e.v >> e.w;

    if (K != N - 1) {
        cout << "Invalid MST\n";
        return 0;
    }

    DSU dsu(N);
    long long cost = 0;
    for (auto &e : cand) {
        if (!dsu.unite(e.u, e.v)) {
            cout << "Invalid MST\n";
            return 0;
        }
        cost += e.w;
    }

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a.w < b.w; });

    DSU d2(N);
    long long mstCost = 0;
    for (auto &e : edges)
        if (d2.unite(e.u, e.v))
            mstCost += e.w;

    if (cost == mstCost) cout << "Valid MST\n";
    else cout << "Invalid MST\n";
}
