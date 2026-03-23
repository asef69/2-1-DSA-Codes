#include<bits/stdc++.h>
using namespace std;
int main(){
    int cards;
    cin>>cards;

    queue<int>player1,player2;

    int k1,k2;
    cin>>k1;
    for(int i=0;i<k1;i++){
        int c; cin>>c;
        player1.push(c);
    }
    cin>>k2;
    for(int i=0;i<k2;i++){
        int c;cin>>c;
        player2.push(c);
    }

    int fights=0,max_fight=1000000;

    while(!player1.empty() && !player2.empty()){
        if(fights>=max_fight){
            cout<<"-1"<<endl;
            return 0;
        }
        int card1=player1.front();
        player1.pop();
        int card2=player2.front();
        player2.pop();

        if(card1>card2){
            player1.push(card2);
            player1.push(card1);
        }
        else{
            player2.push(card1);
            player2.push(card2);
        }
        
        fights++;
        
    }
    

    if(player1.empty()){
        cout<<fights<<" "<<"2"<<endl;
    }
    else{
        cout<<fights<<" "<<"1"<<endl;
    }

}  
