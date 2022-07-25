//bitmask dp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
long long N, K, height[20], dp[1<<17][20], ans;
//dp[s][l]: 사용한 수의 bit state s, 그리고 마지막 수가 l일 때 남은 수들로 만들 수 있는 배열의 개수
long long solve(long long s, long long l){
    long long &r=dp[s][l];
    if(s==(1<<N)-1)
        r=1;
    if(r!=-1)
        return r;
    else{
        r=0;
        long long v=height[l];
        for(long long i=0; i<N; i++){
            if((s & (1<<i))==0){
                if(abs(v-height[i])>K)
                    r+=solve(s | (1<<i), i);
            }
        }
    }
    return r;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> K;
    for(long long i=0; i<N; i++)
        cin >> height[i];
    sort(height, height+N);
    fill(&dp[0][0], &dp[(1<<17)-1][20], -1);
    for(long long i=0; i<N; i++)
        ans+=solve(1<<i, i);
    cout << ans;
    return 0;
}
