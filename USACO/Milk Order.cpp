//USACO 2018 Open Gold 2
//Topological sort & binary search
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int N, M, ind[100010];
vector <int> info[50010], graph[100010], ans;
priority_queue<int, vector<int>, greater<int>> pq;
int check(int k){
    int cnt=0;
    for(int i=1; i<=k; i++){
        for(int j=0; j<info[i].size()-1; j++){
            graph[info[i][j]].push_back(info[i][j+1]);
            ind[info[i][j+1]]++;
        }
    }
    for(int i=1; i<=N; i++)
        if(ind[i]==0) pq.push(i);
    while(!pq.empty()){
        int cur=pq.top();
        cnt++;
        ans.push_back(cur);
        pq.pop();
        for(int nxt : graph[cur]){
            ind[nxt]--;
            if(ind[nxt]==0) pq.push(nxt);
        }
    }
    if(cnt<N) return 0;
    else return 1;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    for(int i=1; i<=M; i++){
        int c; cin >> c;
        for(int j=1; j<=c; j++){
            int v; cin >> v;
            info[i].push_back(v);
        }
    }
    int lo=1, hi=M;
    while(lo<hi){
        int mid=(lo+hi)/2+1;
        if(check(mid)){
            lo=mid;
        }
        else{
            hi=mid-1;
        }
        while(!pq.empty())
            pq.pop();
        for(int i=0; i<100010; i++) graph[i].clear();
        fill(&ind[0], &ind[100010], 0);
        ans.clear();
    }
    check(lo);
    for(int i=0; i<ans.size(); i++){
        cout << ans[i] << " ";
    }
    return 0;
}
