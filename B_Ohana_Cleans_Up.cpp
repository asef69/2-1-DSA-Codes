#include<bits/stdc++.h>
using namespace std;
int main(){
    long long n,i,j,ans;
    while(cin>>n){
        string s;
        vector<string>row;
        for(int i=0;i<n;i++){
            cin>>s;
            row.push_back(s);
        }
        long long  count,ans=0;
        for(int i=0;i<n;i++){
            s=row[i];
            count=1;
            for(int j=0;j<n;j++){
                if(i==j) continue;
                if(s==row[j]) count++;

            }
            ans=max(ans,count);
        }
        cout<<ans<<endl;
    }
}