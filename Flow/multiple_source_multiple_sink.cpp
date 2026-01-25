#include <bits/stdc++.h>
using namespace std;

// Edge and NetworkFlowSolverBase classes from template
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
public:
    static const long long INF = 1e18;
protected:
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
 * Multiple Source and Multiple Sink Max Flow
 * 
 * Problem: Find maximum flow from multiple sources to multiple sinks
 * 
 * Solution: Add a super source connected to all sources with infinite capacity
 *           Add a super sink connected from all sinks with infinite capacity
 *           Solve single-source single-sink max flow
 * 
 * Input format:
 * - Line 1: N M (nodes, edges)
 * - Next M lines: u v c (edge from u to v with capacity c)
 * - Line: numSources s1 s2 ... (source nodes)
 * - Line: numSinks t1 t2 ... (sink nodes)
 */

void solveMultiSourceSink()
{
    long long N, M;
    cin >> N >> M;
    
    // Create graph with 2 extra nodes: super source and super sink
    long long superSource = N;      // Node N is super source
    long long superSink = N + 1;    // Node N+1 is super sink
    long long totalNodes = N + 2;
    
    EdmondsKarpAdjacencyList solver(totalNodes, superSource, superSink);
    
    // Read all edges
    for (long long i = 0; i < M; i++)
    {
        long long u, v, c;
        cin >> u >> v >> c;
        solver.addEdge(u, v, c, i);
    }
    
    // Read sources
    long long numSources;
    cin >> numSources;
    vector<long long> sources(numSources);
    for (long long i = 0; i < numSources; i++)
    {
        cin >> sources[i];
        // Connect super source to each source with infinite capacity
        solver.addEdge(superSource, sources[i], NetworkFlowSolverBase::INF);
    }
    
    // Read sinks
    long long numSinks;
    cin >> numSinks;
    vector<long long> sinks(numSinks);
    for (long long i = 0; i < numSinks; i++)
    {
        cin >> sinks[i];
        // Connect each sink to super sink with infinite capacity
        solver.addEdge(sinks[i], superSink, NetworkFlowSolverBase::INF);
    }
    
    solver.solve();
    
    cout << "Maximum flow from multiple sources to multiple sinks: " 
         << solver.getMaxFlow() << endl;
    
    // Show flow from each source
    cout << "\nFlow from each source:" << endl;
    vector<vector<Edge *> > &graph = solver.getGraph();
    for (size_t i = 0; i < graph[superSource].size(); i++)
    {
        Edge *e = graph[superSource][i];
        if (e->flow > 0)
        {
            cout << "Source " << e->to << ": " << e->flow << endl;
        }
    }
    
    // Show flow to each sink
    cout << "\nFlow to each sink:" << endl;
    for (long long sink : sinks)
    {
        for (size_t i = 0; i < graph[sink].size(); i++)
        {
            Edge *e = graph[sink][i];
            if (e->to == superSink && e->flow > 0)
            {
                cout << "Sink " << sink << ": " << e->flow << endl;
            }
        }
    }
    
    // Show original edge flows
    cout << "\nOriginal edge flows:" << endl;
    for (long long u = 0; u < N; u++)
    {
        for (size_t i = 0; i < graph[u].size(); i++)
        {
            Edge *e = graph[u][i];
            if (e->capacity > 0 && e->capacity < NetworkFlowSolverBase::INF && e->edgeId >= 0)
            {
                cout << u << " -> " << e->to << ": " << e->flow << "/" << e->capacity << endl;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solveMultiSourceSink();
    return 0;
}

/*
Example Input:
6 7
0 2 10
1 2 5
1 3 15
2 4 10
2 5 5
3 5 10
4 5 10
2 0 1
2 4 5

Explanation:
- 6 nodes (0-5), 7 edges
- Edges with capacities
- 2 sources: nodes 0 and 1
- 2 sinks: nodes 4 and 5

Example Output:
Maximum flow from multiple sources to multiple sinks: 25

Flow from each source:
Source 0: 10
Source 1: 15

Flow to each sink:
Sink 4: 10
Sink 5: 15

Original edge flows:
0 -> 2: 10/10
1 -> 2: 5/5
1 -> 3: 10/15
2 -> 4: 10/10
2 -> 5: 5/5
3 -> 5: 10/10
4 -> 5: 0/10

Another Example (Linear chain):
4 3
0 1 10
1 2 5
2 3 8
1 0
1 3

This has source 0, sink 3, max flow = 5 (bottleneck at edge 1->2)
*/