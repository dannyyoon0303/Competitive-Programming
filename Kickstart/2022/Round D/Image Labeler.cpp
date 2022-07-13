#include <iostream>
#include <algorithm>
using namespace std;
int T, N, M;
int A[10010];
int main(){
    cin >> T;
    for(int i=1;i<=T; i++){
        int sum=0;
        cin >> N >> M;
        for(int i=1; i<=N; i++){
            int num; cin >> num;
            A[i]=2*num;
        }
        sort(A+1, A+N+1);
        for(int i=N; i>=N-M+2; i--)
            sum+=A[i];
        int k=N-M+1;
        if(k%2==0)
            sum+=(A[k/2]+A[k/2+1])/2;
        else sum+=A[k/2+1];
        if(sum%2==0)
            cout << "Case #" << i << ": " << sum/2 << ".0"  <<"\n";
        else{
            cout << "Case #" << i << ": " << sum/2 << ".5" << "\n";
        }
    }
    return 0;
}
