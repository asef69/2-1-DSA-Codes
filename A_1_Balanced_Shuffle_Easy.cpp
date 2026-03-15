#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;
    vector<tuple<int,int,char>> a;
    int b=0;
    for(int i=0;i<s.length();i++){
        a.push_back(make_tuple(b,-i,s[i]));
        if(s[i]=='('){
            b+=1;
        }
        else{
            b-=1;
        }
    }
    sort(a.begin(),a.end());
    for(int i=0;i<s.length();i++){
        cout<<std::get<2>(a[i]);
    }
    cout<<endl;
    
}