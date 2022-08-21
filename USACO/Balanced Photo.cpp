//USACO 2017 Jan Gold 1
//Inversion Counting, segment tree
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
int N, lnum[100010], rnum[100010], ans, st[4*100010];
pair<int,int> height[100010];
map <int,int> m;
int query(int nn, int a, int b, int qa, int qb){
    if(qa<=a && b <=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 0;
    int mid=(a+b)/2;
    return query(nn*2, a, mid, qa, qb)+query(nn*2+1, mid+1, b, qa, qb);
}
void update(int nn, int a, int b, int qa, int qb,int val){
    if(qa<=a && b<=qb){
        st[nn]=val;
        return;
    }
    if(qa>b || qb<a) return;
    int mid=(a+b)/2;
    update(2*nn, a, mid, qa, qb, val);
    update(2*nn+1, mid+1, b, qa, qb, val);
    st[nn]=st[nn*2]+st[nn*2+1];
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> height[i].first;
        height[i].second=i;
    }
    sort(height+1, height+N+1);
    for(int i=1; i<=N; i++){
        m[height[i].second]=i;
    }
    for(int i=1; i<=N; i++){
        lnum[i]=query(1, 1, N, m[i], N);
        update(1, 1, N, m[i], m[i], 1);
    }
    fill(&st[0], &st[4*100010], 0);
    for(int i=N; i>=1; i--){
        rnum[i]=query(1, 1, N, m[i], N);
        update(1, 1, N, m[i], m[i], 1);
    }
    for(int i=1; i<=N; i++){
        int g=max(lnum[i], rnum[i]), s=min(lnum[i], rnum[i]);
        if(g>2*s)
            ans++;
    }
    cout << ans;
    return 0;
}
