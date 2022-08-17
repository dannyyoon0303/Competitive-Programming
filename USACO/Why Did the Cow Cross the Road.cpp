//2017 USACO Feb Gold 1
//Dijkstra
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
struct travel{
    long long node, cost;
};
struct cmp{
    bool operator()(travel a, travel b){
        return a.cost > b.cost;
    }
};
vector<pair<long long,long long>> edges[3*10010];
long long N, T, wt[110][110], val[3*10010];
const long long INF=1e11;
long long dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
priority_queue<travel, vector<travel>, cmp> pq;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> T;
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
            cin >> wt[i][j];
    for(long long i=1; i<=N; i++){
        for(long long j=1; j<=N; j++){
            for(long long k=0; k<3; k++){
                long long v=3*(N*(i-1)+j)-k;
                for(long long n=0; n<4; n++){
                    long long nx=i+dx[n], ny=j+dy[n];
                    if(1<=nx && nx<=N && 1<=ny && ny<=N){
                        long long nv=3*(N*(nx-1)+ny)-(k+1)%3;
                        if((k+1)%3==0)
                            edges[v].push_back({nv, T+wt[nx][ny]});
                        else edges[v].push_back({nv, T});
                    }
                }
            }
        }
    }
    for(long long i=0; i<3*10010; i++)
        val[i]=INF;
    val[3]=0;
    pq.push({3, 0});
    while(!pq.empty()){
        auto now=pq.top(); pq.pop();
        if(now.cost>val[now.node]) continue;
        for(auto adj : edges[now.node]){
            if(val[adj.first]>adj.second+now.cost){
                val[adj.first]=adj.second+now.cost;
                pq.push({adj.first, val[adj.first]});
            }
        }
    }
    cout << min(val[3*N*N], min(val[3*N*N-1], val[3*N*N-2]));
    return 0;
}
