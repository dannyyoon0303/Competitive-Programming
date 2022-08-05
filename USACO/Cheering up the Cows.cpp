//USACO November 2008 Gold 2
// MST 
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector <pair<int, pair<int,int>>> edges;

int N, P, p[10010], sz[10010], v[10010];
long long ans;
bool cmp(pair<int, pair<int,int>>&x, pair<int, pair<int,int>>&y){
    return x.first<y.first;
}
int Find(int x){
    if(p[x]==x)
        return x;
    else return p[x]=Find(p[x]);
}
void Union (int a, int b){
    a=Find(a); b=Find(b);
    if(a==b) return;
    if(sz[a]>sz[b]) swap(a, b);
    p[a]=b;
    sz[b]+=sz[a];
}
int main(){
    int mv=1010;
    cin >> N >> P;
    for(int i=1; i<=N; i++){
        p[i]=i; sz[i]=1;
    }
    for(int i=1; i<=N; i++){
        cin >> v[i];
        mv=min(mv, v[i]);
    }
    for(int i=1; i<=P; i++){
        int a, b, c;
        cin >> a >> b >> c;
        int val=2*c+v[a]+v[b];
        edges.push_back({val, {a, b}});
    }
    sort(edges.begin(), edges.end());
    for(int i=0; i<edges.size(); i++){
        int v1=edges[i].second.first, v2=edges[i].second.second;
        if(Find(v1)!=Find(v2)){
            ans+=edges[i].first;
            Union(v1, v2);
        }
    }
    cout << ans+mv;
    return 0;
}
