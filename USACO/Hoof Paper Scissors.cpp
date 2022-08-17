//2017 USACO Jan Gold 2
//DP
#include <iostream>
#include <algorithm>
using namespace std;
//H: 0, P: 1, S: 2
int N, K, dp[100010][3][30], fj[100010], ans;
int solve(int i, int s, int k){
    int &r=dp[i][s][k];
    if(i==N+1)
        r=0;
    if(r!=-1)
        return r;
    else{
        int m=0;
        int w=(fj[i]+1)%3;
        if(s==w){
            m=1+solve(i+1, s, k);
            if(k>=1){
                m=max(m, 1+solve(i+1, (s+1)%3, k-1));
                m=max(m, 1+solve(i+1, (s+2)%3, k-1));
            }
        }
        else{
            m=solve(i+1, s, k);
            if(k>=1){
                m=max(m, solve(i+1, (s+1)%3, k-1));
                m=max(m, solve(i+1, (s+2)%3, k-1));
            }
        }
        r=m;
    }
    return r;
}
int main(){
    cin >> N >> K;
    for(int i=1; i<=N; i++){
        char c;cin >> c;
        if(c=='H') fj[i]=0;
        else if(c=='P') fj[i]=1;
        else fj[i]=2;
    }
    fill(&dp[0][0][30], &dp[100009][2][30], -1);
    ans=max(solve(1, 0, K), max(solve(1, 1, K), solve(1, 2, K)));
    
    cout << ans;
    return 0;
}
