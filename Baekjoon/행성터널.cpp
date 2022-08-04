//COCI
//MST & Math
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
vector <pair<int, pair<int,int>>> edges;
vector <pair<int,int>> x, y, z;
struct Data{
    int x, y, z;
};
int N, p[100010], sz[100010];
long long ans;
Data point[100010];
int dist(int i, int j){
    int v1=abs(point[i].x-point[j].x), v2=abs(point[i].y-point[j].y), v3=abs(point[i].z-point[j].z);
    return min(v1, min(v2, v3));
}
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
    cin >> N;
    for(int i=1; i<=N; i++){
        p[i]=i; sz[i]=1;
    }
    for(int i=1; i<=N; i++){
        int a, b, c;
        cin >> a >> b >> c;
        x.push_back({a,i});
        y.push_back({b,i});
        z.push_back({c,i});
        point[i]={a, b, c};
    }
    sort(x.begin(), x.end());
    sort(y.begin(), y.end());
    sort(z.begin(), z.end());
    for(int i=0; i<=N-2; i++){
        edges.push_back({dist(x[i].second, x[i+1].second), {x[i].second, x[i+1].second}});
        edges.push_back({dist(y[i].second, y[i+1].second), {y[i].second, y[i+1].second}});
        edges.push_back({dist(z[i].second, z[i+1].second), {z[i].second, z[i+1].second}});
    }
    sort(edges.begin(), edges.end());
    for(int i=0; i<edges.size(); i++){
        int u=edges[i].second.first, v=edges[i].second.second;
        if(Find(u)!=Find(v)){
            ans+=edges[i].first;
            Union(u, v);
        }
    }
    cout << ans;
    return 0;
}
