//구간 dp
//https://www.acmicpc.net/problem/3012
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
const long long MOD=100000;
long long N, dp[210][210];
string s, open="([{", close=")]}";
long long solve(long long start, long long end){
    long long &r=dp[start][end];
    if(start>end) r=1;
    if(r!=-1) return r;
    else{
        r=0;
        for(long long i=start+1; i<=end; i+=2){
            for(long long j=0; j<3; j++){
                if(s[start]==open[j] || s[start]=='?'){
                    if(s[i]==close[j] || s[i]=='?'){
                        r+=solve(start+1, i-1)*solve(i+1, end);
                        if(r>=MOD)
                            r=MOD+r%MOD;
                    }
                }
            }
        }
    }
    return r;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    cin >> s;
    fill(&dp[0][0], &dp[209][210], -1);
    long long temp=solve(0, (long long)s.length()-1);
    if(temp>=MOD)
        printf("%05lld\n", temp%MOD);
    else cout << temp << "\n";
    return 0;
}
