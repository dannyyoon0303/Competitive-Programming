//USACO 2019 Feb 
//Delegation
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
using namespace std;
int N, dp[100010], K, ans[100010], mark[100010];
vector <int> graph[100010], son[100010];
int solve(int x){
    multiset<int> s;
    int &r=dp[x];
    if(r!=-1) return r;
    else{
        r=0;
        for(int nxt : son[x]){
            if(solve(nxt)==-2){
                r=-2;
            }
            else{
                int val=(1+solve(nxt))%K;
                if(val!=0){
                    if(s.count(K-val)>0)
                        s.erase(s.find(K-val));
                    else s.insert(val);
                }
               
            }
        }
        if(r!=-2){
            if(s.size()==0) r=0;
            else if(s.size()==1) r=*s.begin();
            else r=-2;
        }
    }
    return r;
}
void dfs(int v){
    mark[v]=1;
    for(int nxt : graph[v])
        if(mark[nxt]==0){
            son[v].push_back(nxt);
            dfs(nxt);
        }
}
int main(){
    //freopen("deleg.in", "r", stdin);
    //freopen("deleg.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1; i<N; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1);
    
    /*K=3;
    fill(&dp[0], &dp[100010], -1);
    solve(1);
    for(int i=1; i<=N; i++)
        cout << dp[i] << "\n";
    cout << "-------\n";*/
    for(int i=1; i<N; i++){
        if((N-1)%i!=0){
            ans[i]=0;
            continue;
        }
        K=i;
        fill(&dp[0], &dp[100010], -1);
        solve(1);
        
        if(dp[1]==0)
            ans[i]=1;
        else ans[i]=0;
    }
    for(int i=1; i<N; i++)
        cout << ans[i];
    
    return 0;
}
