//USACO 2020 Feb Gold 2
//Segment tree, double counting
#include <iostream>
#include <algorithm>
using namespace std;
const long long MOD=1e9+7;
long long N, ans, st[8*100010];
pair<long long,long long> seg[100010];
bool cmp(pair<long long,long long> &x, pair<long long,long long>&y){
    return x.second>y.second;
}
long long query(long long nn, long long a, long long b, long long qa, long long qb){
    if(qa<=a && b <=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 0;
    long long mid=(a+b)/2;
    return query(nn*2, a, mid, qa, qb)+query(nn*2+1, mid+1, b, qa, qb);
}
void update(long long nn, long long a, long long b, long long qa, long long qb,long long val){
    if(qa<=a && b<=qb){
        st[nn]=val;
        return;
    }
    if(qa>b || qb<a) return;
    long long mid=(a+b)/2;
    update(2*nn, a, mid, qa, qb, val);
    update(2*nn+1, mid+1, b, qa, qb, val);
    st[nn]=st[nn*2]+st[nn*2+1];
}
long long power(long long base, long long exp){
    if(exp==0)
        return 1;
    long long temp=power(base, exp/2)%MOD;
    if(exp%2==1)
        return (((temp*temp)%MOD)*base)%MOD;
    else return (temp*temp)%MOD;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(long long i=1;i<=N; i++){
        cin >> seg[i].first >> seg[i].second;
    }
    sort(seg+1, seg+N+1, cmp);
    
    for(long long i=1; i<=N; i++){
        long long s=seg[i].first, e=seg[i].second;
        long long v=query(1, 1, 2*N, 1, e);
        ans+=power(2, N-1-v);
        ans%=MOD;
        update(1, 1, 2*N, s, s, 1);
    }
    cout << ans;
    return 0;
}
