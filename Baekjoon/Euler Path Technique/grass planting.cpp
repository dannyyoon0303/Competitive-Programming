//LCA & segment tree
//https://www.acmicpc.net/problem/5916
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, st[200010*4], height[100010], dp[100010][30], mark[100010], cnt, first[100010], last[100010];
vector <int> graph[100010];
void dfs(int cur, int par, int depth){
    cnt++;first[cur]=cnt;
    mark[cur]=1;
    dp[cur][0]=par;
    height[cur]=depth;
    for(int nxt : graph[cur]){
        if(mark[nxt]==0){
            dfs(nxt, cur, depth+1);
        }
    }
    cnt++;
    last[cur]=cnt;
}
int lca (int a, int b){
    if(height[a]<height[b]) swap(a,b);
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
    if(qa<=a && b<=qb) return st[nn];
    if(qa>b || qb<a) return 0;
    int mid=(a+b)/2;
    return query(nn*2, a, mid, qa, qb)+query(nn*2+1, mid+1, b, qa, qb);
}
void update(int nn, int a, int b, int qa, int qb, int val){
    if(qa<=a && b<=qb){
        st[nn]+=val;
        return;
    }
    if(qa>b || qb<a) return;
    int mid=(a+b)/2;
    update(nn*2, a, mid, qa, qb, val);
    update(nn*2+1, mid+1, b, qa, qb, val);
    st[nn]=st[nn*2]+st[nn*2+1];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
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
        
        int u, v;
        char c; cin >> c >> u >> v;
        if(c=='P'){
            if(height[u]<height[v]) swap(u,v);
            int l=lca(u, v);
            if(l==v){
                update(1, 1, 2*N, first[u], first[u], 1);
                update(1, 1, 2*N, first[v], first[v], -1);
                
            }
            else{
                update(1, 1, 2*N, first[u], first[u], 1);
                update(1, 1, 2*N, first[v], first[v], 1);
                update(1, 1, 2*N, first[l], first[l], -2);
               
            }
            
        }
        else{
            if(height[u]<height[v]) swap(u, v);
            cout << query(1, 1, 2*N, first[u], last[u]) << "\n";
        }
    }
    return 0;
}
