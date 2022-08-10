//https://www.acmicpc.net/problem/6549
//Coordinate compression -> segment tree twice
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
vector <long long> h;
map <long long, long long> m;
long long msize, st[100010*4], lb[100010], rb[100010], height[100010];
long long query(long long nn, long long a, long long b, long long qa, long long qb){
    if(qa<=a && b<=qb)
        return st[nn];
    if(qa>b || qb<a)
        return -1;
    long long mid=(a+b)/2;
    return max(query(nn*2, a, mid, qa, qb), query(nn*2+1, mid+1, b, qa, qb));
}
void update(long long nn, long long a, long long b, long long qa, long long qb, long long val){
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    while(1){
        long long N, ans=0; cin >> N;
        if(N==0) break;
        for(long long i=1; i<=N;i++){
            long long x; cin >> x;
            height[i]=x;
            if(m[x]==0){
                h.push_back(x); m[x]=1;
            }
        }
        sort(h.begin(), h.end());
        msize=(long long)h.size();
        for(long long i=0; i<msize; i++){
            m[h[i]]=i+1;
        }
        
        for(long long i=1; i<=N; i++){
            lb[i]=query(1, 0, msize, 0, m[height[i]]-1);
            update(1, 0, msize, m[height[i]], m[height[i]],i);
        }
        fill(&st[0], &st[100010*4], 0);
        for(long long i=N; i>=1; i--){
            rb[i]=N+1-query(1,0, msize, 0, m[height[i]]-1);
            update(1, 0, msize, m[height[i]], m[height[i]], N+1-i);
        }
        
        for(long long i=1; i<=N; i++){
            ans=max(ans, height[i]*(rb[i]-lb[i]-1));
        }
        cout << ans << "\n";
        fill(&st[0], &st[4*100010], 0);
        m.clear();
        fill(&rb[0], &rb[100010], 0);
        fill(&lb[0], &lb[100010], 0);h.clear();
    }
    return 0;
}
