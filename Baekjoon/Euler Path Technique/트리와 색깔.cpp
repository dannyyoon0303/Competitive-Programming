//offline query, euler path technique, segment tree
//https://www.acmicpc.net/problem/15899
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, C, st[400010*4], color[200010], cnt, first[200010], last[200010], mark[200010], ans;
pair<int,int> q[200010];
const int MOD=1e9+7;
vector <int> graph[200010], cv[200010];
void dfs(int v){
    mark[v]=1;
    cnt++;
    first[v]=cnt;
    for(int nxt : graph[v]){
        if(mark[nxt]==0)
            dfs(nxt);
    }
    cnt++;
    last[v]=cnt;
}
int query(int nn, int a, int b, int qa, int qb){
    if(qa<=a && b<=qb){
        return st[nn];
    }
    if(qa>b || qb<a)
        return 0;
    int mid=(a+b)/2;
    return query(nn*2, a, mid, qa, qb)+query(nn*2+1, mid+1, b, qa, qb);
}
void update(int nn, int a, int b, int qa, int qb, int val){
    if(qa<=a && b<=qb){
        st[nn]=val;
        return;
    }
    if(qa>b || qb<a)
        return;
    int mid=(a+b)/2;
    update(nn*2, a, mid, qa, qb, val);
    update(nn*2+1, mid+1, b, qa, qb, val);
    st[nn]=st[nn*2]+st[nn*2+1];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> C;
    for(int i=1; i<=N; i++){
        cin >> color[i];
        cv[color[i]].push_back(i);
    }
    for(int i=1; i<N; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1);
    for(int i=1; i<=M; i++){
        int v, c;
        cin >> v >> c;
        q[i]={c, v};
    }
    sort(q+1, q+M+1);
    int curc=1;
    for(int i=1; i<=M; i++){
        int c=q[i].first, v=q[i].second;
        while(curc<=c){
            for(int i=0; i<cv[curc].size(); i++){
                update(1, 1, 2*N, first[cv[curc][i]], first[cv[curc][i]],1);
            }
            curc++;
        }
        ans+=query(1, 1, 2*N, first[v], last[v]);
        ans%=MOD;
    }
    cout << ans;
    return 0;
}
