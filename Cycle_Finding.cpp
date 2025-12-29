#include <bits/stdc++.h>
using namespace std;
 
long long dis[10005];
long long parent[10005];
 
class Edge {
public:
    long long a, b, c;
    Edge(long long a, long long b, long long c) {
        this->a = a;
        this->b = b;
        this->c = c;
    }
};
 
int main() {
    long long n, e;
    cin >> n >> e;
    vector<Edge> edge_list;
    while (e--) {
        long long a, b, c;
        cin >> a >> b >> c;
        edge_list.push_back(Edge(a, b, c));
    }
 
    for (long long i = 1; i <= n; i++) {
        dis[i] = 0;
        parent[i] = -1;
    }
 
    long long last_updated_node = -1;
 
    for (long long i = 1; i <= n; i++) {
        last_updated_node = -1;
        for (auto edge : edge_list) {
            long long a = edge.a;
            long long b = edge.b;
            long long c = edge.c;
 
            if (dis[a] + c < dis[b]) {
                dis[b] = dis[a] + c;
                parent[b] = a;
                last_updated_node = b;
            }
        }
    }
 
    if (last_updated_node == -1) {
        cout << "NO\n";
        return 0;
    }
 
    long long cycle_nodes = last_updated_node;
    for (long long i = 0; i < n; i++) {
        cycle_nodes = parent[cycle_nodes];
    }
 
    vector<long long> check_cycle;
    long long current_node = cycle_nodes;
 
    do {
        check_cycle.push_back(current_node);
        current_node = parent[current_node];
    } while (current_node != cycle_nodes);
    check_cycle.push_back(cycle_nodes);
 
    reverse(check_cycle.begin(), check_cycle.end());
 
    cout << "YES\n";
    for (long long v : check_cycle) cout << v << " ";
    cout << "\n";
 
    return 0;
}
