#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;

int main(){

    string s,t;
    cin>>s>>t;
    if(s.length()!=t.length()){
        cout<<-1<<endl;
        return 0;
    }
    int n;
    cin>>n;
    vector<vector<int> >dist(26,vector<int>(26,INF));
    for(int i=0;i<26;i++){
            dist[i][i]=0;
    }

    for(int i=0;i<n;i++){
        string a,b;
        int w;
        cin>>a>>b>>w;
        int u=a[0]-'a';
        int v=b[0]-'a';
        if(w<dist[u][v]){
            dist[u][v]=w;
        }
    }

    for(int k=0;k<26;k++){
        for(int i=0;i<26;i++){
            if(dist[i][k]<INF){
                for(int j=0;j<26;j++){
                    if(dist[k][j]<INF){
                        dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                    }
                }
            }
        }
    }
    int total=0;
    string result="";
    int length=s.length();

    for(int i=0;i<length;i++){
        if(s[i]==t[i]){
            result+=s[i];
            continue;
        }
        int best=INF;
        char bestChar;
        int u=s[i]-'a';
        int v=t[i]-'a';

        for(int c=0;c<26;c++){
            if(dist[u][c]<INF && dist[v][v]<INF){
                int cost=dist[u][c]+dist[v][c];
                if(cost<best){
                    best=cost;
                    bestChar='a'+c;
                }
            }
        }

        if(best==INF){
            cout<<-1<<endl;
            return 0;
        }
        total+=best;
        result+=bestChar;
    }

    cout<<total<<endl;
    cout<<result<<endl;


}