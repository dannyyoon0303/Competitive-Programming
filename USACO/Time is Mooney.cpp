//2020 USACO Jan Gold 1
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, C, dp[1010][1010], m[1010];
//dp[i][j]: 1에서 시작하여 i번쨰 날에 j에 도착할 때 만들 수 있는 최대 비용
vector <int> graph[1010];
int solve(int i, int j){
    int &r=dp[i][j];
    if(i==0 && j!=1){
        r=-1e9;
    }
    if(r!=-1) return r;
    else{
        int mnum=0;
        for(int nxt: graph[j]){
            int t=solve(i-1, nxt);
            if(t>=0)
                mnum=max(mnum, t+m[j]);
        }
        if(mnum==0) r=-1e9;
        else r=mnum;
    }
    return r;
}
int main(){
    int ans=0;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> C;
    for(int i=1; i<=N; i++)
        cin >> m[i];
    for(int i=1; i<=M; i++){
        int u, v; cin>> u >> v;
        graph[v].push_back(u);
    }
    fill(&dp[0][0], &dp[1009][1010], -1);
    dp[0][1]=0;
    for(int i=0; i<=1000; i++)
        ans=max(ans, solve(i, 1)-C*i*i);
    
    cout << ans;
    return 0;
}
