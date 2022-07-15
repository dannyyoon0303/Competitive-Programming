#include <iostream>
#include <algorithm>
using namespace std;
const int IMP=1e9+1;
int T, arr[300010], N, rarr[300010];
pair <int,int> ld[300010], rd[300010];
int main(){
    cin >> T;
    for(int i=1; i<=T; i++){
        int ans=0;
        cin >> N;
        for(int i=1; i<=N; i++){ cin >> arr[i];rarr[N+1-i]=arr[i];}
        //right
        int e=2;
        while(e<=N-1 && arr[e+1]-arr[e]==arr[e]-arr[e-1])
            e++;
        for(int i=1; i<=N; i++){
            if(i==e){
                if(i==N){
                    rd[N]={IMP, 1};break;
                }
                e=i+1;
                while(e<=N-1 && arr[e+1]-arr[e]==arr[e]-arr[e-1])
                    e++;
            }
            if(i<e)
                rd[i]={arr[e]-arr[e-1], e-i+1};
        }
        //left
        e=2;
        while(e<=N-1 && rarr[e+1]-rarr[e]==rarr[e]-rarr[e-1])
            e++;
        for(int i=1; i<=N; i++){
            if(i==e){
                if(i==N){
                    ld[1]={IMP, 1};break;
                }
                e=i+1;
                while(e<=N-1 && rarr[e+1]-rarr[e]==rarr[e]-rarr[e-1])
                    e++;
            }
            if(i<e)
                ld[N+1-i]={rarr[e-1]-rarr[e], e-i+1};
        }
        for(int i=1; i<=N; i++){
            if(i==1){
                ans=max(ans, rd[2].second+1);
            }
            else if (i==N){
                ans=max(ans, ld[N-1].second+1);
            }
            else{
                ans=max(ans, max(ld[i-1].second+1, rd[i+1].second+1));
                int dif=arr[i+1]-arr[i-1];
                if(dif==2*ld[i-1].first && dif==2*rd[i+1].first)
                    ans=max(ans, ld[i-1].second+1+rd[i+1].second);
                else{
                    if(dif==2*ld[i-1].first)
                        ans=max(ans, ld[i-1].second+2);
                    if(dif==2*rd[i+1].first)
                        ans=max(ans, rd[i+1].second+2);
                }
            }
        }
        cout << "Case #" << i << ": " << ans << "\n";
    }
    return 0;
}
