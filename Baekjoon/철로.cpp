//https://www.acmicpc.net/source/47474331
//line sweeping, priorityqueue
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int N, D, ans;
vector <pair<int,int>> seg;
bool cmp(pair<int,int> &x, pair<int,int> &y){
    if(x.second==y.second)
        return x.first < y.first;
    return x.second < y.second;
}
priority_queue<int, vector<int>, greater<int>> pq;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    for(int i=1; i<=N; i++){
        int a, b; cin >> a >> b;
        seg.push_back({min(a,b),max(a,b)});
    }
    cin >> D;
    sort(seg.begin(), seg.end(),cmp);
    for(int i=0; i<seg.size(); i++){
        
        if(seg[i].second-seg[i].first>D)
            continue;
        else{
            pq.push(seg[i].first);
        }
        while(!pq.empty()){
            int t=pq.top();
            if(seg[i].second-t<=D) break;
            else pq.pop();
        }
        ans=max(ans, (int)pq.size());
    }
    cout << ans;
    return 0;
}

