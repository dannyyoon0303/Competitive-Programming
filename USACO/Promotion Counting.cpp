//USACO 2017 Jan Platinum 1
//Offline query, Euler Path Technique, segment tree
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N,st[200010*4], ind[100010], cnt, first[100010], last[100010], ans[100010];
pair<int,int> p[100010];
vector <int> son[100010];
void dfs(int v){
    cnt++;
    first[v]=cnt;
    for(int nxt : son[v])
        dfs(nxt);
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
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> p[i].first;
        p[i].second=i;
    }
    sort(p+1, p+N+1);
    for(int i=1; i<=N; i++){
        ind[i]=p[i].second;
    }
    for(int i=2; i<=N; i++){
        int v; cin >> v;
        son[v].push_back(i);
    }
    dfs(1);
    for(int i=1; i<=N; i++){
        update(1, 1, 2*N, first[i], first[i], 1);
    }
    
    for(int i=1; i<=N; i++){
        int v=ind[i];
        ans[v]=query(1, 1, 2*N, first[v]+1, last[v]);
        update(1, 1, 2*N, first[v], first[v], 0);
    }
    for(int i=1; i<=N; i++){
        cout << ans[i] << "\n";
    }
    return 0;
}
