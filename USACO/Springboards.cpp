//2020 USACO January Gold 3
//dp, coordinate compression, segment tree, monotonic queue
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;
int N, P, dp[200010], st[800100];
//dp[i]: i까지 가는데 세이브할 수 있는 최대 거리
struct Data{
    int x,y,s;
    //s=1: 끝점, s=0: 시작점
};
bool cmp (Data&a, Data&b){
    if(a.y==b.y)
        return a.x<b.x;
    return a.y<b.y;
}
vector<int> x;
vector <Data> p;
map<int,int> xcomp;
map<pair<int,int>, int> m;
map<pair<int,int>, pair<int,int>> mapstart;
int query(int nn, int a, int b, int qa, int qb){
    if(qa<=a && b<=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 0;
    int mid=(a+b)/2;
    return max(query(2*nn, a, mid, qa, qb), query(2*nn+1, mid+1, b, qa, qb));
}
void update(int nn, int a, int b, int qa, int qb, int val){
    if(qa<=a && b<=qb){
        if(st[nn]<val){
            st[nn]=val; return;
        }
        return;
    }
    if(qa>b || qb<a)
        return;
    int mid=(a+b)/2;
    update(2*nn, a, mid, qa, qb, val);
    update(2*nn+1, mid+1, b, qa, qb, val);
    st[nn]=max(st[2*nn], st[2*nn+1]);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> P;
    for(int i=1; i<=P; i++){
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        p.push_back({x1, y1, 0});
        p.push_back({x2, y2, 1});
        
        mapstart[{x2, y2}]={x1,y1};
        
        x.push_back(x1);x.push_back(x2);
    }
    x.push_back(0);x.push_back(N);
    sort(x.begin(), x.end());
    int ind=0;
    xcomp[x[0]]=ind;
    ind++;
    for(int i=1; i<x.size(); i++){
        if(x[i]!=x[i-1]){
            xcomp[x[i]]=ind;
            ind++;
        }
    }
    p.push_back({0,0,0}); p.push_back({N,N,0});
    sort(p.begin(), p.end(), cmp);
    for(int i=0; i<p.size(); i++){
        Data cur=p[i];
        m[{cur.x, cur.y}]=i;
    }
    int MAX=2*P+2;
    dp[0]=0;
    update(1, 0, MAX, 0, 0, 0);
    for(int i=1; i<p.size(); i++){
        Data cur=p[i];
        int val=0;
        if(cur.s==1){
            auto start=mapstart[{cur.x, cur.y}];
            int initsave=dp[m[{start.first, start.second}]]+(cur.x-start.first)+(cur.y-start.second);
            val=initsave;
        }
        val=max(val, query(1, 0, MAX, 0, xcomp[cur.x]));
        dp[i]=val;
        update(1, 0, MAX, xcomp[cur.x], xcomp[cur.x], val);
    }
    
    cout << 2*N-dp[p.size()-1];
    
    return 0;
}
