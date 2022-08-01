//2016 USACO Feb Gold 3
//MST, Union Find
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
long long A, B, N, M, ans, a[2010], b[2010], p[2010*2010], sz[2010*2010];
vector<pair<long long, pair<long long,long long>>> edges;
bool cmp(pair<long long, pair<long long,long long>> &x, pair<long long, pair<long long,long long>>&y){
    return x.first <y.first;
}
long long Find(long long x){
    if(x==p[x]) return x;
    return p[x]=Find(p[x]);
}
void Union(long long a, long long b){
    a=Find(a);
    b=Find(b);
    if(a==b) return;
    if(sz[a]>sz[b]) swap(a,b);
    p[a]=b;
    sz[b]+=sz[a];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> A >> B >> N >> M;
    for(long long i=1; i<=(N+1)*(M+1); i++){
        p[i]=i;
        sz[i]=1;
    }
    for(long long i=1; i<=N; i++)
        cin >> a[i];
    for(long long i=1; i<=M; i++)
        cin >> b[i];
    sort(a+1, a+N+1); sort(b+1, b+M+1);
    a[N+1]=A; b[M+1]=B;
    for(long long i=1; i<=N; i++){
        for(long long j=1; j<=M+1; j++){
            edges.push_back({b[j]-b[j-1], {(N+1)*(j-1)+i, (N+1)*(j-1)+i+1}});
        }
    }
    for(long long i=1; i<=M; i++){
        for(long long j=1; j<=N+1; j++){
            edges.push_back({a[j]-a[j-1], {j+(N+1)*(i-1), j+(N+1)*i}});
        }
    }
    sort(edges.begin(), edges.end(), cmp);
    
    for(long long i=0; i<edges.size(); i++){
        long long v1=edges[i].second.first, v2=edges[i].second.second;
        long long cost=edges[i].first;
        if(Find(v1)!=Find(v2)){
            ans+=cost;
            Union(v1, v2);
        }
    }
    cout << ans;
    return 0;
}

