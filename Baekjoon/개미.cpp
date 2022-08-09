//binary jumping
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, energy[100010], mark[100010], dist[100010], dp[100010][30];
vector <pair<int,int>> graph[100010];
void dfs(int cur, int par){
    mark[cur]=1;
    dp[cur][0]=par;
    for(auto p: graph[cur]){
        int nxt=p.first, cost=p.second;
        if(mark[nxt]==0){
            dist[nxt]=dist[cur]+cost;
            dfs(nxt, cur);
        }
    }
}
int Find(int x){
    int e=energy[x];
    for(int i=20; i>=0; i--){
        int nxt=dp[x][i];
        if(dist[x]-dist[nxt]<=e){
            e-=(dist[x]-dist[nxt]);
            x=nxt;
        }
    }
    return x;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> energy[i];
    }
    for(int i=1; i<N; i++){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    dfs(1, 1);
    for(int j=1; j<=20; j++){
        for(int i=1; i<=N; i++){
            dp[i][j]=dp[dp[i][j-1]][j-1];
        }
    }
    
    for(int i=1; i<=N; i++){
        cout << Find(i) << "\n";
    }
    return 0;
}
