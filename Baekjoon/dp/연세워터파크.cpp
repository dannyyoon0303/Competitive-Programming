#include <iostream>
#include <algorithm>
using namespace std;
long long N, D, val[100010], dp[100010], st[4*100010];
//dp[i]: i번째 다리에서 끝날 때 만들 수 있는 최대 점수
long long query(long long nn, long long a, long long b, long long qa, long long qb){
    if(qa<=a && b<=qb)
        return st[nn];
    if(qa>b || qb<a)
        return -1e9-1;
    long long mid=(a+b)/2;
    return max(query(nn*2, a, mid, qa, qb), query(nn*2+1, mid+1, b, qa, qb));
}
void update(long long nn, long long a,long long b, long long qa, long long qb, long long val){
    if(qa<=a && b<=qb){
        st[nn]=val;
        return;
    }
    if(qa>b || qb<a)
        return;
    long long mid=(a+b)/2;
    update(nn*2, a, mid, qa, qb, val);
    update(nn*2+1, mid+1, b, qa, qb, val);
    st[nn]=max(st[nn*2], st[nn*2+1]);
}
int main(){
    long long ans=-1e9-1;
    cin >> N >> D;
    for(long long i=1; i<=N; i++)
        cin >> val[i];
    dp[1]=val[1];
    ans=val[1];
    update(1, 1, N, 1, 1, dp[1]);
    for(long long i=2; i<=N; i++){
        long long v=query(1, 1, N, max(1, (int)(i-D)), i)+val[i];
        dp[i]=v;
        ans=max(ans, dp[i]);
        update(1, 1, N, i, i, dp[i]);
    }
    cout << ans;
    return 0;
}

