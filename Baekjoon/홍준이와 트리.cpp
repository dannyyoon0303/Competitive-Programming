//Euler path technique & Segment Tree
//https://www.acmicpc.net/problem/13030
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
long long N, Q, height[300010], H, cnt, first[300010], last[300010];
long long msize, mark[300010];
const long long MOD=1e9+7;
pair<long long,long long> st[600010*4];
vector <long long> son[300010];
void dfs(long long v, long long depth){
    height[v]=depth;
    H=max(H, height[v]);
    cnt++;
    first[v]=cnt;
    for(long long nxt : son[v])
        dfs(nxt, depth+1);
    cnt++;
    last[v]=cnt;
}
pair<long long,long long> query(long long nn, long long a, long long b, long long qa, long long qb){
    if(qa<=a && b<=qb)
        return st[nn];
    if(qa>b || qb<a)
        return {0,0};
    long long mid=(a+b)/2;
    auto p1=query(nn*2, a, mid, qa, qb), p2=query(nn*2+1, mid+1, b, qa, qb);
    return {(p1.first+p2.first)%MOD, (p1.second+p2.second)%MOD};
}
void update(long long nn, long long a, long long b, long long qa, long long qb, long long v1, long long v2){
    if(qa<=a && b<=qb){
        st[nn].first+=v1;
        st[nn].second+=v2;
        st[nn].first=(st[nn].first+MOD)%MOD;
        st[nn].second=(st[nn].second+MOD)%MOD;
        return;
    }
    if(qa>b || qb<a)
        return;
    long long mid=(a+b)/2;
    update(nn*2, a, mid, qa, qb, v1, v2);
    update(nn*2+1, mid+1, b, qa, qb, v1, v2);
    st[nn]={(st[nn*2].first+st[nn*2+1].first)%MOD, (st[nn*2].second+st[nn*2+1].second)%MOD};
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    for(long long i=2; i<=N; i++){
        long long p;
        cin >> p;
        son[p].push_back(i);
    }
    dfs(1,1);
    for(long long i=1; i<=Q; i++){
        long long c; cin >> c;
        if(c==1){
            long long v, x, k;
            cin >> v >> x >> k;
            long long num=(x-(k*(H-height[v]))%MOD+MOD)%MOD;
            update(1, 1, N*2, first[v], first[v], num, k);
            update(1, 1, N*2, last[v], last[v], -num, -k);
        }
        else{
            long long v;
            cin >> v;
            auto temp=query(1, 1, N*2, 1, first[v]);
            long long ans=temp.first+temp.second*(H-height[v]);
            cout << ans%MOD << "\n";
        }
    }
    return 0;
}
