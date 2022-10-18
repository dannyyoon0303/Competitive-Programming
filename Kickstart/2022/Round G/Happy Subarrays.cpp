#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long T, N, st[4*400010], arr[400010], p[400010];
pair<long long,long long> loc[400010];
long long query(long long nn, long long a, long long b, long long qa, long long qb){
    if(qa<=a && b <=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 1e9;
    long long mid=(a+b)/2;
    return min(query(nn*2, a, mid, qa, qb),query(nn*2+1, mid+1, b, qa, qb));
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
    st[nn]=min(st[nn*2],st[nn*2+1]);
}
int main(){
    cin >> T;
    for(long long i=1; i<=T; i++){
        long long ans=0;
        fill(&st[0], &st[4*400010], 1e9);
        cin >> N;
        arr[0]=0;p[0]=0;loc[0]={0,0};
        for(long long i=1; i<=N; i++){
            long long x; cin >> x;
            arr[i]=arr[i-1]+x;
            loc[i]={arr[i], i};
        }
        for(long long i=1; i<=N+1; i++){
            p[i]=p[i-1]+arr[i-1];
        }
        sort(loc, loc+N+1);
        for(long long i=0; i<=N; i++)
            update(1, 0, N, i,i, N+1);
        for(long long i=0; i<=N; i++){
            long long ind=loc[i].second;
            long long ub=query(1, 0, N, ind, N);
            //cout << ind << " " << ub << "\n";
            if(ub==N+1){
                long long temp=p[N+1]-p[ind+1]-(N-ind)*arr[ind];
                ans+=temp;
                update(1,0,N, ind, ind, ind);
            }
            else{
                ub--;
                long long temp=p[ub+1]-p[ind+1]-(ub-ind)*arr[ind];
                ans+=temp;
                update(1,0,N,ind,ind,ind);
            }
            //cout << ind << " " << ans << "\n";
        }
        cout << "Case #" << i << ": " << ans << "\n";
    }
    return 0;
}
