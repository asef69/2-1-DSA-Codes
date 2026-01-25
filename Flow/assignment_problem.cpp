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
 * Assignment Problem using Max Flow
 * 
 * Problem: Assign N workers to N tasks, where each worker can do certain tasks
 * with different capacities/costs. Maximize total assignments.
 * 
 * Input format:
 * - Line 1: N (number of workers and tasks)
 * - Next lines: worker task capacity
 * - End with: -1 -1 -1
 * 
 * This is essentially maximum bipartite matching with capacities
 */

void solveAssignmentProblem()
{
    long long N; // N workers, N tasks
    cin >> N;
    
    // Node layout: 0 = source, 1..N = workers, N+1..2N = tasks, 2N+1 = sink
    long long source = 0;
    long long sink = 2 * N + 1;
    long long totalNodes = 2 * N + 2;
    
    EdmondsKarpAdjacencyList solver(totalNodes, source, sink);
    
    // Add edges from source to all workers with capacity 1 (each worker does 1 task)
    for (long long i = 1; i <= N; i++)
    {
        solver.addEdge(source, i, 1);
    }
    
    // Add edges from all tasks to sink with capacity 1 (each task done by 1 worker)
    for (long long i = 1; i <= N; i++)
    {
        solver.addEdge(N + i, sink, 1);
    }
    
    // Read worker-task assignments with capacities
    long long worker, task, capacity;
    while (cin >> worker >> task >> capacity)
    {
        if (worker == -1) break;
        // worker is 1..N, task is 1..N
        // Map task to node N+task
        solver.addEdge(worker, N + task, capacity);
    }
    
    solver.solve();
    
    cout << "Total assignments: " << solver.getMaxFlow() << endl;
    cout << "Assignment details:" << endl;
    
    // Extract assignments
    vector<vector<Edge *> > &graph = solver.getGraph();
    for (long long w = 1; w <= N; w++)
    {
        for (size_t i = 0; i < graph[w].size(); i++)
        {
            Edge *e = graph[w][i];
            if (e->capacity > 0 && e->flow > 0 && e->to != source)
            {
                long long taskNode = e->to - N;
                cout << "Worker " << w << " assigned to Task " << taskNode 
                     << " (flow: " << e->flow << ")" << endl;
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solveAssignmentProblem();
    return 0;
}

/*
Example Input:
3
1 1 1
1 2 1
2 2 1
2 3 1
3 1 1
3 3 1
-1 -1 -1

Example Output:
Total assignments: 3
Assignment details:
Worker 1 assigned to Task 1 (flow: 1)
Worker 2 assigned to Task 2 (flow: 1)
Worker 3 assigned to Task 3 (flow: 1)

Another Example (with capacities > 1):
3
1 1 2
2 2 3
3 3 1
-1 -1 -1

Output would show max 3 assignments (limited by source/sink edges)
*/