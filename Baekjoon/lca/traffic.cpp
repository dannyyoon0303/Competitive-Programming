//segment tree, euler path technique, lca
//https://www.acmicpc.net/problem/12746
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int MAX=222232;
int N, Q, height[MAX], mark[MAX], dp[MAX][30], cnt=1, start[MAX], last[MAX], st[8*MAX];
vector <int> graph[MAX];
void dfs(int cur, int par, int depth){
    start[cur]=cnt;
    cnt++;
    mark[cur]=1;
    height[cur]=depth;
    dp[cur][0]=par;
    for(int nxt : graph[cur]){
       if(mark[nxt]==0){
           dfs(nxt, cur, depth+1);
       }
    }
    last[cur]=cnt;
    cnt++;
}
int lca(int a, int b){
    if(height[a]<height[b]) swap(a, b);
    for(int i=20; i>=0; i--){
        int nxt=dp[a][i];
        if(height[nxt]>=height[b])
            a=nxt;
    }
    if(a==b) return a;
    for(int i=20; i>=0; i--){
        int aa=dp[a][i];
        int bb=dp[b][i];
        if(aa!=bb){
            a=aa; b=bb;
        }
    }
    return dp[a][0];
}
int query(int nn, int a, int b, int qa, int qb){
    if(qa<=a && b <=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 0;
    int mid=(a+b)/2;
    return query(nn*2, a, mid, qa, qb)+query(nn*2+1, mid+1, b, qa, qb);
}
void update(int nn, int a, int b, int qa, int qb,int val){
    if(qa<=a && b<=qb){
        st[nn]+=val;
        return;
    }
    if(qa>b || qb<a) return;
    int mid=(a+b)/2;
    update(2*nn, a, mid, qa, qb, val);
    update(2*nn+1, mid+1, b, qa, qb, val);
    st[nn]=st[nn*2]+st[nn*2+1];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    for(int i=1; i<N; i++){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, 1, 1);
    for(int j=1; j<=20; j++){
        for(int i=1; i<=N; i++)
            dp[i][j]=dp[dp[i][j-1]][j-1];
    }
    for(int i=1;i<=Q; i++){
        int a, b; cin >> a >> b;
        int l=lca(a,b);
        update(1, 1, 2*N, start[a], start[a], 1);
        update(1, 1, 2*N, start[b], start[b], 1);
        update(1, 1, 2*N, start[l], start[l], -2);
    }
    int ans=0;
    pair<int,int> anspair;
    for(int i=2; i<=N; i++){
        int val=query(1, 1, 2*N, start[i], last[i]);
        if(val>ans){
            ans=val;
            if(dp[i][0]<i) anspair={dp[i][0], i};
            else anspair={i, dp[i][0]};
        }
    }
    
    cout << anspair.first << " " << anspair.second << " " << ans;
    return 0;
}
