//2020 USACO Feb Gold 1
//dp, topological sort
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int N, M, C, mb[100010], dp[100010];
vector <pair<int,int>> son[100010];
int solve(int x){
    int &r=dp[x];
    if(r!=-1)
        return r;
    else{
        int m=mb[x];
        for(auto p : son[x]){
            int nxt=p.first, gap=p.second;
            m=max(m, gap+solve(nxt));
        }
        r=m;
    }
    return r;
}
int main(){
    cin >> N >> M >> C;
    for(int i=1; i<=N; i++){
        cin >> mb[i];
    }
    for(int i=1; i<=N; i++){
        dp[i]=-1;
    }
    for(int i=1; i<=C; i++){
        int u, v, g;
        cin >> u >> v >> g;
        son[v].push_back({u, g});
    }
    for(int i=1; i<=N; i++)
        cout << solve(i) << "\n";
    return 0;
}
