#include<bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin>>s;

    stack<char>st;
    for(int i=0;i<s.length();i++){
        st.push(s[i]);
        if(st.size()>=3){
            char c=st.top();st.pop();
            char b=st.top();st.pop();
            char a=st.top();st.pop();
            if(a=='A' && b=='B' && c=='C'){
            }
            else{
                st.push(a);
                st.push(b);
                st.push(c);
            }
        }
    }
    string result="";
    while(!st.empty()){
        result+=st.top();
        st.pop();
    }
    reverse(result.begin(),result.end());
    cout<<result;

}