//USACO 2021 Jan Gold 2
//Dijkstra
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
using namespace std;
const long long INF=1e11;
long long N, K, val[50010], breed[50010], check[60][60];
vector<long long> b[60];
struct travel{
    long long node, cost;
};
struct cmp{
    bool operator()(travel a, travel b){
        return a.cost>b.cost;
    }
};
vector<pair<long long, long long>> edges[50010];
priority_queue<travel, vector<travel>, cmp> pq;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    for(long long i=1; i<=N; i++){
        cin >> breed[i];
        b[breed[i]].push_back(i);
    }
    for(long long i=1; i<=K; i++){
        string s; cin >> s;
        for(long long j=0;j<s.length();j++){
            check[i][j+1]=s[j]-'0';
        }
    }
    for(long long i=1;i<=N; i++){
        long long t=breed[i];
        if(check[t][breed[N]]==1)
            edges[i].push_back({N, abs(N-i)});
        for(long long j=1; j<=K; j++){
            if(check[t][j]==0 || b[j].size()==0) continue;
            long long ub=(long long)(upper_bound(b[j].begin(), b[j].end(), i)-b[j].begin());
            if(ub==b[j].size()){
                ub--;
                if(b[j][ub]==i) ub--;
                if(ub>=0) edges[i].push_back({b[j][ub], abs(b[j][ub]-i)});
            }
            else{
                long long lb=ub-1;
                if(lb>=0 && b[j][lb]==i) lb--;
                if(lb<0) edges[i].push_back({b[j][ub], abs(b[j][ub]-i)});
                else{
                    edges[i].push_back({b[j][ub], abs(b[j][ub]-i)});
                    edges[i].push_back({b[j][lb], abs(b[j][lb]-i)});
                }
            }
        }
    }
    pq.push({1, 0});
    for(long long i=1; i<=N; i++) val[i]=INF; val[1]=0;
    while(!pq.empty()){
        auto now=pq.top(); pq.pop();
        if(now.cost > val[now.node]) continue;
        for(auto adj : edges[now.node]){
            if(val[adj.first]>adj.second+now.cost){
                val[adj.first]=adj.second+now.cost;
                pq.push({adj.first, val[adj.first]});
            }
        }
    }
    
    if(val[N]==INF)
        cout << -1;
    else cout << val[N];
    return 0;
}
