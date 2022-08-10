//bitmask dp
//https://www.acmicpc.net/problem/1029
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int N, price[16][16], dp[1<<16][15][10];
int solve(int s, int k, int p){
    int &r=dp[s][k][p];
    if(r!=-1)
        return r;
    else{
        r=0;
        for(int i=0; i<N; i++){
            if((s & (1<<i))==0){
                if(price[k][i]>=p)
                    r=max(r, 1+solve(s|(1<<i),i, price[k][i]));
            }
        }
    }
    return r;
}
int main(){
    cin >> N;
    for(int i=0; i<N; i++){
        string s; cin >> s;
        for(int j=0; j<N; j++)
            price[i][j]=s[j]-'0';
    }
    fill(&dp[0][0][0], &dp[(1<<16)-1][14][10], -1);
    cout << 1+solve(1<<0,0, 0);
    return 0;
}
