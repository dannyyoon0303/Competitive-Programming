//multiset, binarysearch(lowerbound), greedy
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
long long N, K;
pair<long long,long long> jewel[300010];
multiset <long long> weight;
int main(){
    long long ans=0;
    cin >> N >> K;
    for(long long i=1; i<=N; i++){
        cin >> jewel[i].second >> jewel[i].first;
    }
    sort(jewel+1, jewel+N+1);
    for(long long i=1; i<=K; i++){
        long long v;
        cin >> v;
        weight.insert(v);
    }
    for(long long i=N; i>=1; i--){
        auto l=weight.lower_bound(jewel[i].second);
        if(l!=weight.end()){
            ans+=jewel[i].first;
            weight.erase(weight.find(*l));
        }
    }
    cout << ans;
    return 0;
}
