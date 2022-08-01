//USACO 2016 January Gold 2
//DP
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
long long N, M, dx[3]={0,1,1}, dy[3]={1,0,1}, dp[1010][1010];
//dp[i][j]: i,j까지 간 상태에서 N, M까지 가는데 필요한 최소비용
pair<long long,long long> F, B, Fp[1010], Bp[1010];
string f, b;
long long dist(pair<long long,long long> a, pair<long long,long long> b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}
long long solve(long long i, long long j){
    long long &r=dp[i][j];
    if(i==N && j==M)
        r=0;
    if(r!=-1) return r;
    else{
        if(i==N){
            r=solve(i, j+1)+dist(Fp[i], Bp[j+1]);
        }
        else if(j==M){
            r=solve(i+1, j)+dist(Fp[i+1], Bp[j]);
        }
        else{
            long long v1=solve(i, j+1)+dist(Fp[i], Bp[j+1]), v2=solve(i+1, j)+dist(Fp[i+1], Bp[j]), v3=solve(i+1, j+1)+dist(Fp[i+1], Bp[j+1]);
            r=min(v1, min(v2, v3));
        }
    }
    return r;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    cin >> Fp[0].first >> Fp[0].second;
    cin >> Bp[0].first >> Bp[0].second;
    cin >> f >> b;
    f=' '+f; b=' '+b;
    for(long long i=1; i<=N; i++){
        pair<long long,long long> p=Fp[i-1];
        if(f[i]=='N') Fp[i]={p.first, p.second+1};
        else if (f[i]=='S') Fp[i]={p.first, p.second-1};
        else if (f[i]=='W') Fp[i]={p.first-1, p.second};
        else Fp[i]={p.first+1, p.second};
    }
    for(long long i=1; i<=M; i++){
        pair<long long,long long> p=Bp[i-1];
        if(b[i]=='N') Bp[i]={p.first, p.second+1};
        else if (b[i]=='S') Bp[i]={p.first, p.second-1};
        else if (b[i]=='W') Bp[i]={p.first-1, p.second};
        else Bp[i]={p.first+1, p.second};
    }
    
    fill(&dp[0][0], &dp[1009][1010], -1);
    cout << solve(0,0);
    return 0;
}
