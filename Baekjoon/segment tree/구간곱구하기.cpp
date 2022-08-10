//segment tree beginner
//https://www.acmicpc.net/problem/11505
#include <iostream>
#include <algorithm>
using namespace std;
const long long MOD=1e9+7;
long long N,M, K, st[4*1000010];
long long query(long long nn, long long a, long long b, long long qa, long long qb){
    if(qa<=a && b<=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 1;
    long long mid=(a+b)/2;
    return (query(nn*2, a, mid, qa, qb)*query(nn*2+1, mid+1, b, qa, qb))%MOD;
}
void update(long long nn, long long a, long long b, long long qa,long long qb, long long val){
    if(qa<=a && b<=qb){
        st[nn]=val;
        return;
    }
    if(qa>b || qb<a)
        return;
    long long mid=(a+b)/2;
    update(nn*2, a, mid, qa, qb, val);
    update(nn*2+1, mid+1, b, qa, qb, val);
    st[nn]=(st[nn*2]*st[nn*2+1])%MOD;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> K;
    for(long long i=0; i<4*1000010; i++)
        st[i]=1;
    for(long long i=1; i<=N; i++){
        long long v; cin >> v;
        update(1, 1, N, i, i, v);
    }
    for(long long i=1; i<=M+K; i++){
        long long a, b, c;
        cin >> a >> b >> c;
        if(a==1)
            update(1, 1, N, b, b, c);
        else{
            cout << query(1, 1, N, b, c) << "\n";
        }
    }
    return 0;
}
