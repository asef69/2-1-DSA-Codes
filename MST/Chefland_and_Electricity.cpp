#include<bits/stdc++.h>
using namespace std;
int main(){
    long long test;
    cin>>test;
    while(test--){
        long long n;
        cin>>n;
        string electricity;
        cin>>electricity;
        vector<long long>cordinates(n+1);
        for(int i=1;i<=n;i++){
            cin>>cordinates[i];
        }

        vector<long long>selected(n+1,0);
        vector<long long>distance(n+1,LLONG_MAX);

        priority_queue<array<long long,2>,vector<array<long long,2> >,greater<array<long long,2> > >pq;
        for(int i=0;i<n;i++){
            if(electricity[i]=='1'){
                distance[i+1]=0;
                pq.push({0,i+1});
            }
        } 
        long long ans=0;

        while(!pq.empty()){
            auto front=pq.top();
            pq.pop();

            long long u=front[1];
            long long dist=front[0];

            if(selected[u]) continue;
            selected[u]=1;
            ans+=dist;

            for(long long v:{u-1,u+1}){
                if(v>=1 && v<=n && !selected[v]){
                    long long cost=abs(cordinates[u]-cordinates[v]);
                    if(cost<distance[v]){
                        distance[v]=cost;
                        pq.push({cost,v});
                    }
                }
            }
        }
        cout<<ans<<endl;
    }
}