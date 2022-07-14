#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
long long T, D, N, K;
set <pair<long long,long long>> ks, w;
vector <pair<long long,long long>> v[300010];
int main(){
    cin >> T;
    long long H[300010];
    for(long long i=1; i<=T; i++){
        long long ans=0, sum=0;
        cin >> D >> N >> K;
        for(long long i=1; i<=N; i++){
            long long h, s, e;
            cin >> h >> s >> e;
            H[i]=h;
            v[s].push_back({1, i});v[e+1].push_back({-1, i});
        }
        
        for(long long i=1; i<=D+1; i++){
            if(v[i].size()>0){
                for(long long j=0; j<v[i].size(); j++){
                    auto cur=v[i][j];long long val=H[cur.second];
                    if(cur.first==1){
                        if(ks.size()<K){
                            sum+=val;ks.insert({val, cur.second});
                        }
                        else{
                            if(val>(*ks.begin()).first){
                                auto fv=*ks.begin();
                                sum+=(val-fv.first);
                                ks.erase(fv);w.insert(fv);ks.insert({val, cur.second});
                            }
                            else w.insert({val, cur.second});
                        }
                    }
                    else{
                        if(w.count({val, cur.second}))
                            w.erase({val, cur.second});
                        else{
                            ks.erase({val, cur.second});sum-=val;
                            if(w.size()>0){
                                auto it=w.end(); it--;
                                sum+=(*it).first;
                                w.erase(*it);ks.insert(*it);
                            }
                        }
                    }
                }
                ans=max(ans, sum);
            }
            else continue;
        }
        cout << "Case #" << i << ": " << ans << "\n";
        ks.clear();
        w.clear();
        for(long long i=1; i<=D+1; i++)
            v[i].clear();
    }
    return 0;
}
