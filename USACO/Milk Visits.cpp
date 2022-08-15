//2019 USACO December Gold 2
//Offline query, lca
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, T[100010], height[100010], ps[100010], mark[100010], dp[100010][30];
vector <int> graph[100010];
vector <pair<int,int>> check[100010];

int ans[100010];
void dfs(int cur, int par, int depth){
    mark[cur]=1;
    dp[cur][0]=par;
    height[cur]=depth;
    for(int nxt : graph[cur]){
        if(mark[nxt]==0)
            dfs(nxt, cur, depth+1);
    }
}
int lca(int a, int b){
    if(height[a] < height[b]) swap(a,b);
    for(int i=20; i>=0; i--){
        int nxt=dp[a][i];
        if(height[nxt]>=height[b])
            a=nxt;
    }
    if(a==b) return a;
    for(int i=20; i>=0; i--){
        int aa = dp[a][i];
        int bb=dp[b][i];
        if(aa!=bb){
            a=aa;
            b=bb;
        }
    }
    return dp[a][0];
}
void solve(int v){
    mark[v]=1;
    ps[T[v]]++;
    for(int i=0; i<check[v].size(); i++){
        auto cur=check[v][i];
        if(cur.second>0){
            ans[cur.first]+=ps[cur.second];
        }
        else{
            ans[cur.first]-=2*ps[-cur.second];
            if(T[v]==-cur.second) ans[cur.first]++;
        }
    }
    for(int nxt: graph[v]){
        if(mark[nxt]==0)
            solve(nxt);
    }
    ps[T[v]]--;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    for(int i=1; i<=N; i++)
        cin >> T[i];
    for(int i=1; i<N; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1,1,1);
    for(int j=1; j<=20; j++){
        for(int i=1; i<=N; i++)
            dp[i][j]=dp[dp[i][j-1]][j-1];
    }
    for(int i=1; i<=M; i++){
        int u, v, t; cin >> u >> v >> t;
        int l=lca(u,v);
        check[u].push_back({i, t});
        check[v].push_back({i, t});
        check[l].push_back({i, -t});
    }
    
    fill(&mark[0], &mark[100010], 0);
    solve(1);
    for(int i=1; i<=M; i++){
        if(ans[i]>0) cout << 1;
        else cout << 0;
    }
    return 0;
}
