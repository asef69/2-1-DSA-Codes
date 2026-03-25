#include<bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    cin>>n>>m;
    multiset<int> price;
    for(int i=0;i<n;i++){
        int c;
        cin>>c;
        price.insert(c);
    }
    for(int i=0;i<m;i++){
        int b;
        cin>>b;
        auto it = price.upper_bound(b);
        if(it == price.begin()){
            cout<<-1<<'\n';
        }else{
            --it;
            cout<<*it<<'\n';
            price.erase(it);
        }
    }
    return 0;
}