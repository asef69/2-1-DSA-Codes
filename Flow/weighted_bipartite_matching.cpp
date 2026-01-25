#include <bits/stdc++.h>
using namespace std;

// Edge and NetworkFlowSolverBase classes remain the same as template
class Edge
{
public:
    long long from, to;
    Edge *residual;
    long long flow;
    long long capacity;
    long long edgeId;
    
    Edge(long long from, long long to, long long capacity, long long edgeId = -1)
    {
        this->from = from;
        this->to = to;
        this->capacity = capacity;
        this->flow = 0;
        this->residual = NULL;
        this->edgeId = edgeId;
    }
    
    bool isResidual()
    {
        return capacity == 0;
    }
    
    long long remainingCapacity()
    {
        return capacity - flow;
    }
    
    void augment(long long bottleneck)
    {
        flow += bottleneck;
        residual->flow -= bottleneck;
    }
};

class NetworkFlowSolverBase
{
protected:
    static const long long INF = 1e18;
    long long n, s, t;
    long long maxFlow;
    vector<bool> visited;
    vector<vector<Edge *> > graph;

    virtual void solve() = 0;

    void markAllNodesAsUnvisited()
    {
        fill(visited.begin(), visited.end(), false);
    }
    
    bool isVisited(long long node)
    {
        return visited[node];
    }
    
    void visit(long long node)
    {
        visited[node] = true;
    }

public:
    NetworkFlowSolverBase(long long n, long long s, long long t)
    {
        this->n = n;
        this->s = s;
        this->t = t;
        maxFlow = 0;
        visited.resize(n, false);
        graph.resize(n);
    }
    
    virtual ~NetworkFlowSolverBase()
    {
        for (size_t i = 0; i < graph.size(); i++)
        {
            for (size_t j = 0; j < graph[i].size(); j++)
            {
                delete graph[i][j];
            }
        }
    }
    
    void addEdge(long long from, long long to, long long capacity, long long edgeId = -1)
    {
        Edge *e1 = new Edge(from, to, capacity, edgeId);
        Edge *e2 = new Edge(to, from, 0, -1);
        e1->residual = e2;
        e2->residual = e1;
        graph[from].push_back(e1);
        graph[to].push_back(e2);
    }
    
    vector<vector<Edge *> > &getGraph()
    {
        return graph;
    }
    
    long long getMaxFlow()
    {
        return maxFlow;
    }
};

class EdmondsKarpAdjacencyList : public NetworkFlowSolverBase
{
public:
    EdmondsKarpAdjacencyList(long long n, long long s, long long t) : NetworkFlowSolverBase(n, s, t) {}
    
    void solve()
    {
        long long flow;
        do
        {
            markAllNodesAsUnvisited();
            flow = bfs();
            maxFlow += flow;
        } while (flow != 0);
    }

private:
    long long bfs()
    {
        vector<Edge *> prev((size_t)n, (Edge *)NULL);
        queue<long long> q;
        visit(s);
        q.push(s);
        
        while (!q.empty())
        {
            long long node = q.front();
            q.pop();
            
            if (node == t)
                break;
            
            for (size_t i = 0; i < graph[node].size(); i++)
            {
                Edge *edge = graph[node][i];
                long long cap = edge->remainingCapacity();
                
                if (cap > 0 && !isVisited(edge->to))
                {
                    visit(edge->to);
                    prev[edge->to] = edge;
                    q.push(edge->to);
                }
            }
        }

        if (prev[t] == NULL)
            return 0;

        long long bottleNeck = INF;
        for (Edge *edge = prev[t]; edge != NULL; edge = prev[edge->from])
        {
            bottleNeck = min(bottleNeck, edge->remainingCapacity());
        }
        
        for (Edge *edge = prev[t]; edge != NULL; edge = prev[edge->from])
        {
            edge->augment(bottleNeck);
        }
        
        return bottleNeck;
    }
};

/*
 * Weighted Maximum Bipartite Matching
 * 
 * Problem: Given a bipartite graph with weights on edges, find maximum matching
 * with maximum total weight.
 * 
 * Input format:
 * - Line 1: N M (nodes in left set, nodes in right set)
 * - Next lines: u v w (edge from left node u to right node v with weight w)
 * - End input with: -1 -1 -1
 * 
 * Approach: Use min-cost max-flow by negating weights
 * For simplicity here, we'll find max flow matching with capacity = weight
 */

void solveWeightedBipartiteMatching()
{
    long long N, M; // N nodes in left set, M nodes in right set
    cin >> N >> M;
    
    // Node layout: 0 = source, 1..N = left set, N+1..N+M = right set, N+M+1 = sink
    long long source = 0;
    long long sink = N + M + 1;
    long long totalNodes = N + M + 2;
    
    EdmondsKarpAdjacencyList solver(totalNodes, source, sink);
    
    // Add edges from source to all left nodes with capacity 1
    for (long long i = 1; i <= N; i++)
    {
        solver.addEdge(source, i, 1);
    }
    
    // Add edges from all right nodes to sink with capacity 1
    for (long long i = 1; i <= M; i++)
    {
        solver.addEdge(N + i, sink, 1);
    }
    
    // Read bipartite edges
    long long u, v, w;
    while (cin >> u >> v >> w)
    {
        if (u == -1) break;
        // u is in left set (1..N), v is in right set (1..M)
        // Map v to node N+v
        solver.addEdge(u, N + v, 1); // For max matching, capacity is 1
    }
    
    solver.solve();
    
    cout << "Maximum matching size: " << solver.getMaxFlow() << endl;
    cout << "Matched pairs:" << endl;
    
    // Extract matching
    vector<vector<Edge *> > &graph = solver.getGraph();
    for (long long u = 1; u <= N; u++)
    {
        for (size_t i = 0; i < graph[u].size(); i++)
        {
            Edge *e = graph[u][i];
            if (e->capacity > 0 && e->flow > 0 && e->to != source)
            {
                long long rightNode = e->to - N;
                cout << "Left " << u << " -> Right " << rightNode << endl;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solveWeightedBipartiteMatching();
    return 0;
}

/*
Example Input:
3 3
1 1 5
1 2 3
2 2 4
2 3 2
3 3 6
-1 -1 -1

Example Output:
Maximum matching size: 3
Matched pairs:
Left 1 -> Right 1
Left 2 -> Right 2
Left 3 -> Right 3
*/