#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
long long T, B[5010], N, K, m[1000010];
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    for(long long i=1; i<=T; i++){
        long long ans=5010;
        cin >> N >> K;
        for(int i=1; i<=K; i++) m[i]=0;
        m[0]=1;
        for(long long i=1; i<=N; i++){
            cin >> B[i];
        }
        for(long long i=N; i>=1; i--){
            long long sum=0;
            for(long long j=i; j>=1; j--){
                sum+=B[j];
                if(sum>K) break;
                if(K-sum>=0 && m[K-sum]>=1) ans=min(ans, m[K-sum]+i-j);
            }
            sum=0;
            for(long long j=i; j<=N; j++){
                sum+=B[j];
                if(sum>K) break;
                if(sum!=0){
                    if(m[sum]>1) m[sum]=min(m[sum], j-i+2);
                    else m[sum]=j-i+2;
                }
            }
        }
        if(ans!=5010) cout << "Case #" << i << ": " << ans << "\n";
        else cout << "Case #" << i << ": " << -1 << "\n";
    }
    return 0;
}

