#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    vector<int>candies(n+1,0);
    for(int i=1;i<=n;i++){
        cin>>candies[i];
    }
    queue<int> q;
    queue<int>index;
    for(int i=1;i<=n;i++){
        q.push(candies[i]);
        index.push(i);
    }
    while(q.size()!=1){
        int candy=q.front();
        int idx=index.front();
        q.pop();
        index.pop();
        if(candy>m){
            candy-=m;
            q.push(candy);
            index.push(idx);
        }
    }
    cout<<index.front();
}

