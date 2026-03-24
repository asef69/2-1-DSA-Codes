#include<bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin>>n;
    deque<int> dq;
    for(int i=0;i<n;i++){

        int id;
        cin>>id;
        if(i%2==0) dq.push_front(id);
        else dq.push_back(id);
    }
    if(n%2==1){
        while(!dq.empty()){
            cout<<dq.front()<<" ";
            dq.pop_front();
        }
    }
    else{
        while(!dq.empty()){
            cout<<dq.back()<<" ";
            dq.pop_back();
        }
    }
    cout<<endl;
}