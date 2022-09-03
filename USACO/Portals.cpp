//USACO 2021 US Open Gold 2
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, p[4*100010], sz[4*100010], v[100010][5], ans;
int Find(int x){
    if(p[x]==x) return x;
    return p[x]=Find(p[x]);
}
void Union (int a, int b){
    a=Find(a); b=Find(b);
    
    if(a==b) return;
    if(sz[a]>sz[b]) swap(a,b);
    p[a]=b;
    sz[b]+=sz[a];
}
pair <int, int> cost[100010];
vector <int> portal[2*100010];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1; i<=4*N; i++){
        p[i]=i;
        sz[i]=1;
    }
    for(int i=1; i<=N; i++){
        int c;
        cin >> c;
        cost[i]={c, i};
        cin >> v[i][1] >> v[i][2] >> v[i][3] >> v[i][4];
        for(int j=1; j<=4; j++)
            portal[v[i][j]].push_back(i);
        Union(2*i-1, 2*N+v[i][1]); Union(2*i-1, 2*N+v[i][2]);
        Union(2*i, 2*N+v[i][3]); Union(2*i, 2*N+v[i][4]);
    }
    for(int i=2*N+1; i<=4*N; i++){
        int ptl=i-2*N;
        for(int j=0; j<2; j++){
            int vtx=portal[ptl][j];
            for(int k=1; k<=4; k++){
                if(v[vtx][k]==ptl){
                    if(k<=2)
                        Union(i, 2*vtx-1);
                    else Union(i, 2*vtx);
                }
            }
        }
    }
    
    sort(cost+1, cost+N+1);
    for(int i=1; i<=N; i++){
        int u=2*cost[i].second-1, v=2*cost[i].second;
        if(Find(u)!=Find(v)){
            ans+=cost[i].first;
            Union(u, v);
        }
    }
    cout << ans;
    return 0;
}
