//USACO 2020 Jan Gold 2
#include <iostream>
#include <algorithm>
using namespace std;
const long long B=1e6;
long long N, Q, dp[5010][5010], a[5010], mark[2000010], ts[5010][5010];
long long solve(long long i, long long j){
    long long &r=dp[i][j];
    if(j-i<=1)
        r=0;
    if(r!=-1)
        return r;
    else{
        r=solve(i+1, j)+solve(i, j-1)-solve(i+1, j-1)+ts[i][j];
    }
    return r;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    fill(&dp[0][0], &dp[5009][5010], -1);
    for(long long i=1; i<=N; i++)
        cin >> a[i];
    for(long long i=1; i<N; i++){
        for(long long j=i+1; j<=N; j++){
            long long v=-a[i]-a[j]+B;
            if(v>=0 && v<2000010)
                ts[i][j]=mark[v];
            mark[a[j]+B]++;
        }
        for(long long j=N; j>=i+1; j--){
            mark[a[j]+B]--;
        }
    }
    
    for(long long i=1; i<=Q; i++){
        long long u, v; cin >> u >> v;
        cout << solve(u, v) << "\n";
    }
    return 0;
}
