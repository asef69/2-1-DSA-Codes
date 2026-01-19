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

vector<vector<pair<int,long long>>> mstTree;

bool findPathAndMaxWeight(int currentNode, int targetNode, int parentNode, long long &maxWeight) {
    if (currentNode == targetNode) return true;
    for (auto [nextNode, edgeWeight] : mstTree[currentNode]) {
        if (nextNode == parentNode) continue;
        long long previousMax = maxWeight;
        maxWeight = max(maxWeight, edgeWeight);
        if (findPathAndMaxWeight(nextNode, targetNode, currentNode, maxWeight)) return true;
        maxWeight = previousMax;
    }
    return false;
}

int main() {
    int numNodes, numEdges;
    cin >> numNodes >> numEdges;
    vector<Edge> edges(numEdges);
    for (auto &e : edges) cin >> e.u >> e.v >> e.w;

    sort(edges.begin(), edges.end(),
         [](auto &a, auto &b){ return a.w < b.w; });

    DSU dsu(numNodes);
    long long mstCost = 0;
    mstTree.assign(numNodes, {});

    vector<bool> inMST(numEdges, false);

    for (int i = 0; i < numEdges; i++) {
        if (dsu.unite(edges[i].u, edges[i].v)) {
            mstCost += edges[i].w;
            inMST[i] = true;
            mstTree[edges[i].u].push_back({edges[i].v, edges[i].w});
            mstTree[edges[i].v].push_back({edges[i].u, edges[i].w});
        }
    }

    long long secondBestMSTCost = LLONG_MAX;
    for (int i = 0; i < numEdges; i++) {
        if (inMST[i]) continue;
        long long maxWeightInPath = 0;
        findPathAndMaxWeight(edges[i].u, edges[i].v, -1, maxWeightInPath);
        secondBestMSTCost = min(secondBestMSTCost, mstCost + edges[i].w - maxWeightInPath);
    }

    cout << mstCost << "\n";
    if (secondBestMSTCost == LLONG_MAX) cout << -1 << "\n";
    else cout << secondBestMSTCost << "\n";
}
