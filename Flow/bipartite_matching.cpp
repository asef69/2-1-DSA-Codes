#include <bits/stdc++.h>
using namespace std;

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

void solveBipartiteMatching()
{
    long long N, K, M;
    cin >> N >> K >> M;
    
    long long source = N;
    long long sink = N + 1;
    
    EdmondsKarpAdjacencyList solver(N + 2, source, sink);
    
    for (long long i = 0; i < K; i++)
    {
        solver.addEdge(source, i, 1);
    }
    
    for (long long i = K; i < N; i++)
    {
        solver.addEdge(i, sink, 1);
    }
    
    vector<pair<long long, long long> > compatibilityEdges;
    
    for (long long i = 0; i < M; i++)
    {
        long long u, v;
        cin >> u >> v;
        compatibilityEdges.push_back({u, v});
        solver.addEdge(u, v, 1);
    }
    
    solver.solve();
    
    long long maxMatching = solver.getMaxFlow();
    
    cout << maxMatching << endl;
    
    vector<vector<Edge *> > &graph = solver.getGraph();
    vector<pair<long long, long long> > matches;
    
    for (long long officer = 0; officer < K; officer++)
    {
        for (size_t i = 0; i < graph[officer].size(); i++)
        {
            Edge *edge = graph[officer][i];
            if (edge->to >= K && edge->to < N && edge->flow == 1 && edge->capacity == 1)
            {
                matches.push_back({officer, edge->to});
            }
        }
    }
    
    for (size_t i = 0; i < matches.size(); i++)
    {
        cout << matches[i].first << " " << matches[i].second << endl;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solveBipartiteMatching();
    return 0;
}
