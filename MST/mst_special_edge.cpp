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
    int N, M, K;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;
    cin >> K;

    vector<int> special(K);
    for (int &x : special) cin >> x;

    long long ans = LLONG_MAX;

    for (int idx : special) {
        DSU dsu(N);
        long long cost = edges[idx].w;
        dsu.unite(edges[idx].u, edges[idx].v);
        int cnt = 1;

        for (int i = 0; i < M; i++) {
            if (i == idx) continue;
            if (dsu.unite(edges[i].u, edges[i].v)) {
                cost += edges[i].w;
                cnt++;
            }
        }
        if (cnt == N - 1) ans = min(ans, cost);
    }

    if (ans == LLONG_MAX) cout << -1 << "\n";
    else cout << ans << "\n";
}
