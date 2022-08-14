//https://www.acmicpc.net/problem/9470
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
int T, ind[1010], ord[1010];
vector <int> graph[1010];
pair <int, int> vm[1010];
queue <int> q;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    for(int i=1; i<=T; i++){
        int K, M, P;
        cin >> K >> M >> P;
        for(int i=1; i<=P; i++){
            int a, b;
            cin >> a >> b;
            graph[a].push_back(b);
            ind[b]++;
        }
        for(int i=1; i<=M; i++)
            if(ind[i]==0){
                q.push(i);
                ord[i]=1;
            }
        while(!q.empty()){
            int cur=q.front();q.pop();
            for(int nxt: graph[cur]){
                ind[nxt]--;
                if(vm[nxt].first==ord[cur]){
                    vm[nxt].second++;
                }
                else if(ord[cur]>vm[nxt].first){
                    vm[nxt]={ord[cur], 1};
                }
                if(ind[nxt]==0){
                    q.push(nxt);
                    if(vm[nxt].second>1) ord[nxt]=vm[nxt].first+1;
                    else ord[nxt]=vm[nxt].first;
                }
            }
        }
        
        cout << i << " " << ord[M] << "\n";
        fill(&ind[0], &ind[1010], 0);
        fill(&ord[0], &ord[1010], 0);
        for(int i=0; i<1010; i++)
            vm[i]={0,0};
        for(int i=0; i<1010; i++) graph[i].clear();
        
    }
    return 0;
}
