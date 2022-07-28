//dfs TLE avoid
#include <iostream>
#include <algorithm>
using namespace std;
int N, board[15][15], mark[30], ans1, ans2;
void odfs(int s, int c){
    if(s==2*N+2){
        ans1=max(ans1, c);
        return;
    }
    for(int i=1; i<=min(s, N); i++){
        if(s-i>=1 && s-i<=N){
            if(mark[N+s-i-i]==0 && board[i][s-i]==1){
                mark[N+s-i-i]=1;
                odfs(s+2, c+1);
                mark[N+s-i-i]=0;
            }
        }
    }
    odfs(s+2, c);
}
void edfs(int s, int c){
    if(s==2*N+1){
        ans2=max(ans2, c);
        return;
    }
    for(int i=1; i<=min(s, N); i++){
        if(s-i>=1 && s-i<=N){
            if(mark[N+s-i-i]==0 && board[i][s-i]==1){
                mark[N+s-i-i]=1;
                edfs(s+2, c+1);
                mark[N+s-i-i]=0;
            }
        }
    }
    edfs(s+2, c);
}
int main(){
    cin >> N;
    for(int i=1;i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> board[i][j];
        }
    }
    odfs(2, 0);edfs(3,0);
    cout << ans1+ans2;
    
    return 0;
}

