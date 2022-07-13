#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
long long T, N, C;
vector <pair<long long,long long>> mark, ps;
map <long long, long long> m;
bool cmp(pair<long long,long long> x, pair<long long,long long> y){
    if(x.first==y.first)
        return x.second < y.second;
    else
        return x.first<y.first;
}
int main(){
    cin >> T;
    for(long long i=1; i<=T; i++){
        cin >> N >> C;
        long long ans=N;
        for(long long i=1; i<=N; i++){
            long long l, r;
            cin >> l >> r;
            mark.push_back({l+1, 1});mark.push_back({r, -1});
        }
        sort(mark.begin(), mark.end(), cmp);
        
        for(long long i=0; i<mark.size(); i++){
            if(i==0){
                m[mark[0].first]=mark[0].second;
            }
            else{
                if(mark[i].first==mark[i-1].first){
                    m[mark[i].first]+=mark[i].second;
                }
                else{
                    ps.push_back({m[mark[i-1].first], mark[i].first-mark[i-1].first});
                    m[mark[i].first]+=(m[mark[i-1].first]+mark[i].second);
                }
            }
        }
        sort(ps.begin(), ps.end(), cmp);
        
        for(long long i=(long long)ps.size()-1; i>=0; i--){
            long long val=ps[i].first, n=ps[i].second;
            if(n>C){
                ans+=C*val;break;
            }
            else{
                ans+=val*n;
                C-=n;
            }
        }
        cout << "Case #" << i << ": " << ans << "\n";
        mark.clear();ps.clear();m.clear();
    }
    return 0;
}
