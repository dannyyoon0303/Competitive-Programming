//USACO 2020 US Open Gold 1
//Segment tree
#include <iostream>
#include <algorithm>
using namespace std;
long long N, A[100010], st[4*100010];
pair<long long,long long> arr[100010];
bool cmp(pair<long long,long long>&x, pair<long long,long long>&y){
    if(x.first==y.first)
        return x.second<y.second;
    return x.first<y.first;
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
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(long long i=1; i<=N; i++){
        cin >> A[i];
        arr[i]={A[i], i};
    }
    sort(arr+1, arr+N+1, cmp);
    long long ans=0, v=1;
    for(long long k=0; k<N; k++){
        if(k==0)
            cout << 0 << "\n";
        else{
            while(v<=N && arr[v].first<k){
                long long index=arr[v].second;
                ans+=(index-1-query(1, 1, N, 1, index));
                update(1, 1, N, index, index, 1);
                v++;
            }
            cout << ans << "\n";
        }
    }
    return 0;
}
