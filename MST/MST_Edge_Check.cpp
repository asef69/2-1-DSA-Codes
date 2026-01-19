#include<bits/stdc++.h>
using namespace std;
class Disjoint_Set_Union{
private:
vector<long long>parent;
vector<long long>rank;
public:
Disjoint_Set_Union(long long n){
    parent.resize(n+1);
    rank.resize(n+1,0);
    for(long long i=1;i<=n;i++){
        parent[i]=i;
    }
}
long long find(long long x){
    if(parent[x]!=x){
        parent[x]=find(parent[x]);
    }
    return parent[x];
}

bool unite_node(long long x,long long y){
    long long rootX=find(x);
    long long rootY=find(y);
    if(rootX==rootY){
        return false;
    }
    if(rank[rootX]<rank[rootY]){
        parent[rootX]=rootY;
    }
    else if(rank[rootX]>rank[rootY]){
        parent[rootY]=rootX;
    }
    else{
        parent[rootY]=rootX;
        rank[rootX]++;
    }
    return true;
}

bool same_set(long long x, long long y) {
    return find(x) == find(y);
}

};
bool compare_edges(const pair<long long,pair<long long,long long> >&a,const pair<long long,pair<long long,long long> >&b){
    if(a.first!=b.first){
        return a.first<b.first;
    }
    if(a.second.first!=b.second.first){
        return a.second.first<b.second.first;
    }

    return a.second.second<b.second.second;

}

void kruskal_algorithm(vector<pair<long long,pair<long long,long long> > >&edges,long long n){
    map<pair<long long, pair<long long, long long>>, long long> edge_to_index;
    for(long long i = 0; i < edges.size(); i++) {
        edge_to_index[make_pair(edges[i].first, make_pair(edges[i].second.first, edges[i].second.second))] = i;
    }
    
    vector<pair<long long,pair<long long,long long> > > sorted_edges = edges;
    sort(sorted_edges.begin(),sorted_edges.end(),compare_edges);

    Disjoint_Set_Union dsu(n+1);
    vector<bool> result(edges.size(), false);
    
    long long i = 0;
    while(i < sorted_edges.size()) {
        long long j = i;
        while(j < sorted_edges.size() && sorted_edges[j].first == sorted_edges[i].first) {
            j++;
        }
        

        for(long long k = i; k < j; k++) {
            long long u = sorted_edges[k].second.first;
            long long v = sorted_edges[k].second.second;
            

            long long orig_idx = edge_to_index[make_pair(sorted_edges[k].first, make_pair(u, v))];
            
            if(!dsu.same_set(u, v)) {
                result[orig_idx] = true;
            }
        }
        

        for(long long k = i; k < j; k++) {
            long long u = sorted_edges[k].second.first;
            long long v = sorted_edges[k].second.second;
            dsu.unite_node(u, v);
        }
        
        i = j;
    }
    

    for(long long i = 0; i < result.size(); i++) {
        if(result[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
int main(){
    long long n,m;
    cin>>n>>m;
    vector<vector<pair<long long,long long> > >adj(n+1);
    vector<pair<long long, pair<long long,long long> > >edges;

    for(long long i=0;i<m;i++){
        long long a,b,w;
        cin>>a>>b>>w;
        adj[a].push_back(make_pair(b,w));
        adj[b].push_back(make_pair(a,w));

        edges.push_back(make_pair(w,make_pair(a,b)));
    }

    kruskal_algorithm(edges,n);
}