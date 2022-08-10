//MST
//https://www.acmicpc.net/problem/4792
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, K, p[1010], sz[1010];
vector <pair<int, pair<int,int>>> edges1, edges2;
bool cmp(pair<int, pair<int,int>>&x, pair<int, pair<int,int>>&y){
    return x.first < y.first;
}
int Find(int x){
    if(p[x]==x) return x;
    return p[x]=Find(p[x]);
}
void Union (int a, int b){
    a=Find(a); b=Find(b);
    if(a==b) return;
    if(sz[a]>sz[b]) swap(a,b);
    sz[b]+=sz[a];
    p[a]=b;
}
int main(){
    while(1){
        int minb=0, minr=0;
        cin >> N >> M >> K;
        if(N==0 && M==0 && K==0) break;
        edges1.clear(); edges2.clear();
        for(int i=1; i<=M; i++){
            char c; int u, v;
            cin >> c >> u >> v;
            if(c=='B'){
                edges1.push_back({1, {u,v}});
                edges2.push_back({0, {u,v}});
            }
            else{
                edges1.push_back({0, {u,v}});
                edges2.push_back({1, {u,v}});
            }
        }
        sort(edges1.begin(), edges1.end(), cmp);
        sort(edges2.begin(), edges2.end(), cmp);
        for(int i=1; i<=N; i++){
            p[i]=i; sz[i]=1;
        }
        for(int i=0; i<edges1.size(); i++){
            int u=edges1[i].second.first, v=edges1[i].second.second;
            if(Find(u)!=Find(v)){
                minb+=edges1[i].first; Union(u,v);
            }
        }
        for(int i=1; i<=N; i++){
            p[i]=i; sz[i]=1;
        }
        for(int i=0; i<edges2.size(); i++){
            int u=edges2[i].second.first, v=edges2[i].second.second;
            if(Find(u)!=Find(v)){
                minr+=edges2[i].first; Union(u,v);
            }
        }
        if(minb<=K && K<=N-1-minr) cout << 1 << "\n";
        else cout << 0 << "\n";
    }
    
    
    return 0;
}
