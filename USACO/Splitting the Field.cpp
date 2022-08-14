//USACO 2016 March Gold 1
//Sweeping, geometry
#include <iostream>
#include <algorithm>
using namespace std;
long long N, oa, ans;
pair <long long,long long> xp[50010], yp[50010], rxp[50010], lxp[50010], ryp[50010], lyp[50010];//first: min, second: max
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(long long i=1; i<=N; i++){
        long long x, y; cin >> x >> y;
        xp[i]={x, y}; yp[i]={y, x};
    }
    sort(xp+1, xp+N+1); sort(yp+1, yp+N+1);
    oa=(xp[N].first-xp[1].first)*(yp[N].first-yp[1].first);
    for(long long i=1; i<=N; i++){
        if(i==1) {
            rxp[i]={xp[i].second, xp[i].second};
            lxp[i]={xp[N+1-i].second, xp[N+1-i].second};
            ryp[i]={yp[i].second, yp[i].second};
            lyp[i]={yp[N+1-i].second, yp[N+1-i].second};
        }
        else{
            rxp[i]={min(xp[i].second, rxp[i-1].first), max(xp[i].second, rxp[i-1].second)};
            lxp[i]={min(xp[N+1-i].second, lxp[i-1].first), max(xp[N+1-i].second, lxp[i-1].second)};
            ryp[i]={min(yp[i].second, ryp[i-1].first), max(yp[i].second, ryp[i-1].second)};
            lyp[i]={min(yp[N+1-i].second, lyp[i-1].first), max(yp[N+1-i].second, lyp[i-1].second)};
        }
    }
    
    for(long long i=1; i<=N-1; i++){
        long long ar;
        ar=(xp[i].first-xp[1].first)*(rxp[i].second-rxp[i].first)+(xp[N].first-xp[i+1].first)*(lxp[N-i].second-lxp[N-i].first);
        ans=max(ans, oa-ar);
        ar=(yp[i].first-yp[1].first)*(ryp[i].second-ryp[i].first)+(yp[N].first-yp[i+1].first)*(lyp[N-i].second-lyp[N-i].first);
        ans=max(ans, oa-ar);
    }
    cout << ans;
    return 0;
}
