/*KOI 2003 중등부 2번
DP reducing conditions*/
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int N, W, dp[1010][1010], mark[1010];
//dp[i][j]: 경찰차 1,2가 마지막으로 맡은 사건이 각각 i,j일 때 나머지 사건 처리할 때 필요한 최소이동거리
pair <int,int> h[1010];
int dist(int x1, int y1, int x2, int y2){
    return abs(x1-x2)+abs(y1-y2);
}
int solve(int i, int j){
    int &r=dp[i][j];
    if(i==W || j==W) r=0;
    if(r!=-1)
        return r;
    else{
        int nxt=max(i, j)+1;
        if(j==0){
            r=min(dist(h[i].first, h[i].second, h[nxt].first, h[nxt].second)+solve(nxt, j), dist(N, N, h[nxt].first, h[nxt].second)+solve(i, nxt));
        }
        else
            r=min(dist(h[i].first, h[i].second, h[nxt].first, h[nxt].second)+solve(nxt, j), dist(h[j].first, h[j].second, h[nxt].first, h[nxt].second)+solve(i, nxt));
    }
    return r;
}
void dfs(int i, int j){
    int nxt=max(i,j)+1;
    if(i==W || j==W) return;
    if(j==0){
        int v1=dist(h[i].first, h[i].second, h[nxt].first, h[nxt].second)+dp[nxt][j], v2=dist(N, N, h[nxt].first, h[nxt].second)+dp[i][nxt];
        if(v1<v2) {mark[nxt]=1;dfs(nxt, j);}
        else {mark[nxt]=2;dfs(i, nxt);}
    }
    else{
        int v1=dist(h[i].first, h[i].second, h[nxt].first, h[nxt].second)+dp[nxt][j], v2=dist(h[j].first, h[j].second, h[nxt].first, h[nxt].second)+dp[i][nxt];
        if(v1<v2){ mark[nxt]=1;dfs(nxt, j);}
        else {mark[nxt]=2;dfs(i, nxt);}
    }
}
int main(){
    cin >> N >> W;
    for(int i=1;i<=W; i++)
        cin >> h[i].first >> h[i].second;
    h[0]={1,1};
    fill(&dp[0][0], &dp[1009][1010], -1);
    solve(0,0);
    dfs(0,0);
    cout << dp[0][0] << "\n";
    for(int i=1; i<=W; i++)
        cout << mark[i] << "\n";
    return 0;
}
