#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
long long T, N, M, K, A[6010], B[6010], pA[6010], pB[6010], Asum, Bsum;
long long mA[6010], mB[6010], ans;
int main(){
    cin >> T;
    for(long long i=1;i<=T; i++){
        cin >> N;
        for(long long i=1;i<=N;i++)
            cin >> A[i];
        for(long long i=1; i<=N; i++)
            pA[i]=pA[i-1]+A[i];
        Asum=pA[N];
        for(long long i=1; i<=N; i++){
            long long k=N-i, m=0;
            for(long long j=1; j+k-1<=N; j++){
                long long ej=j+k-1;
                m=max(m, Asum-(pA[ej]-pA[j-1]));
            }
            mA[i]=m;
        }
        cin >> M;
        for(long long i=1; i<=M; i++)
            cin >> B[i];
        for(long long i=1; i<=M; i++)
            pB[i]=pB[i-1]+B[i];
        Bsum=pB[M];
        for(long long i=1; i<=M; i++){
            long long k=M-i, m=0;
            for(long long j=1; j+k-1<=M; j++){
                long long ej=j+k-1;
                m=max(m, Bsum-(pB[ej]-pB[j-1]));
            }
            mB[i]=m;
        }
        cin >> K;
        ans=0;
        for(long long i=0; i<=K; i++){
            if(i<=N && K-i<=M)
                ans=max(ans, mA[i]+mB[K-i]);
        }
        cout << "Case #" << i << ": " << ans << "\n";
    }
    return 0;
}
