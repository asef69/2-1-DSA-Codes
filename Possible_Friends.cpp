#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    while(t--){
        int m;
        string firstRow;
        cin>>firstRow;
        m=firstRow.size();

        vector<vector<bool> > friends(m,vector<bool>(m,false));

        for(int j=0;j<m;j++){
            friends[0][j]=(firstRow[j]=='Y');
        }
        for(int i=1;i<m;i++){
            string row;
            cin>>row;
            for(int j=0;j<m;j++){

                friends[i][j]=(row[j]=='Y');
            }
        }
        int maxFriend=0;
        int bestPossible=0;

        for(int i=0;i<m;i++){
            int count=0;
            for(int j=0;j<m;j++){
                if(j==i || friends[i][j]) continue;

                bool found=false;
                for(int k=0;k<m && !found;k++){
                    if(k!=i && j!=i && friends[i][k]&& friends[k][j]){
                        found=true;
                    }
                }
                if(found) count++;
            }
            if(count>maxFriend){
                maxFriend=count;
                bestPossible=i;
            }
        }

        cout<<bestPossible<< " "<<maxFriend<<endl;
    }
}