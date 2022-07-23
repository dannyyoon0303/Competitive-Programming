/*2013 KOI 고등부 3번
Inversion counting & Fenwick Tree*/
#include <iostream>
#include <algorithm>
using namespace std;
long long N, arr[500010], fw[500010], mark[1000010];
long long query(long long p){
    long long ret=0;
    for(; p; p-=p&-p)
        ret+=fw[p];
    return ret;
}
void update(long long p, long long v){
    for( ; p<500010; p+=p&-p)
        fw[p]+=v;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    long long ans=0;
    cin >> N;
    for(long long i=1; i<=N; i++){
        int n; cin >> n;
        mark[n]=i;
    }
    for(long long i=1; i<=N; i++){
        int n; cin >> n;
        arr[i]=mark[n];
    }
    for(long long i=N; i>=1; i--){
        ans+=query(arr[i]);
        update(arr[i], 1);
    }
    cout << ans;
    return 0;
}
