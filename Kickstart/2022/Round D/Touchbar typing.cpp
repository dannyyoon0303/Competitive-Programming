#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
int T, N, M, dp[2510][2510], type[2510], ldist[2510][2510], rdist[2510][2510];
int loc[2510];
int solve(int i, int j){
    int &r=dp[i][j];
    if(i==N)
        r=0;
    if(r!=-1)
        return r;
    else{
        int m=1e9;
        int nxt=type[i+1], p1, p2;
        p1=ldist[j][nxt]; p2=rdist[j][nxt];
        if(p1!=1e9) m=min(m, p1+solve(i+1, j-p1));
        if(p2!=1e9) m=min(m, p2+solve(i+1, j+p2));
        r=m;
    }
    return r;
}
int main(){
    cin >> T;
    for(int i=1;i<=T; i++){
        int ans=1e9;
        cin >> N;
        for(int i=1; i<=N; i++)
            cin >> type[i];
        cin >> M;
        for(int i=1; i<=M; i++){
            cin >> loc[i];
        }
        fill(&ldist[0][0], &ldist[2509][2510], 1e9);
        fill(&rdist[0][0], &rdist[2509][2510], 1e9);
        for(int i=1; i<=M; i++){
            for(int j=i; j>=1; j--){
                ldist[i][loc[j]]=min(ldist[i][loc[j]], i-j);
            }
            for(int j=i+1; j<=M; j++){
                rdist[i][loc[j]]=min(rdist[i][loc[j]], j-i);
            }
        }
        fill(&dp[0][0], &dp[2509][2510], -1);
        int start=type[1];
        for(int i=1; i<=M; i++){
            if(loc[i]==start)
                ans=min(ans, solve(1, i));
        }
        cout << "Case #" << i << ": " << ans << "\n";
    }
    return 0;
}
