//USACO 2016 December Gold 1
//Binary search
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, dist[1010][1010], mark[1010];
vector <int> graph[1010];
pair<int,int> P[1010];
void dfs(int v){
    mark[v]=1;
    for(int nxt : graph[v]){
        if(mark[nxt]==0)
            dfs(nxt);
    }
}
int check(int k){
    int cnt=0;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(i!=j && dist[i][j]<=k)
                graph[i].push_back(j);
        }
    }
    for(int i=1; i<=N; i++){
        if(mark[i]==0){
            cnt++;
            dfs(i);
        }
    }
    if(cnt==1) return 1;
    else return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1; i<=N; i++)
        cin >> P[i].first >> P[i].second;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            dist[i][j]=(P[i].first-P[j].first)*(P[i].first-P[j].first)+(P[i].second-P[j].second)*(P[i].second-P[j].second);
        }
    }
    int lo=1, hi=1e9;
    while(lo<hi){
        int mid=(lo+hi)/2;
        if(check(mid))
            hi=mid;
        else lo=mid+1;
        fill(&mark[0], &mark[1010], 0);
        for(int i=0; i<1010; i++)
            graph[i].clear();
    }
    cout << lo;
    return 0;
}
