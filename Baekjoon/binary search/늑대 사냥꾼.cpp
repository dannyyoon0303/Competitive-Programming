//https://www.acmicpc.net/problem/2917
//binary search + bfs
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;
int N, M, L, mark[510][510], board[510][510];
int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1}, val[510][510];
pair<int,int>start, dest;
vector<pair<int,int>> tree;
queue<pair<int,int>> q;
void dfs(int x, int y){
    mark[x][y]=1;
    if(x==dest.first && y==dest.second)
        return;
    for(int i=0; i<4; i++){
        int nx=x+dx[i], ny=y+dy[i];
        if(1<=nx && nx<=N && 1<=ny && ny<=M){
            if(mark[nx][ny]==0 && board[nx][ny]-1>=L)
                dfs(nx, ny);
        }
    }
}
int check(int k){
    L=k;
    if(board[start.first][start.second]-1>=L)
        dfs(start.first, start.second);
    if(mark[dest.first][dest.second]==1)
        return 1;
    return 0;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        string s; cin >> s;
        for(int j=1; j<=M; j++){
            if(s[j-1]=='+'){
                q.push({i,j});
                board[i][j]=1;
            }
            else if(s[j-1]=='V') start={i,j};
            else if(s[j-1]=='J') dest={i, j};
        }
    }
    //bfs
    while(!q.empty()){
        auto cur=q.front(); q.pop();
        for(int i=0; i<4; i++){
            int nx=cur.first+dx[i], ny=cur.second+dy[i];
            if(1<=nx && nx<=N && 1<=ny && ny<=M && board[nx][ny]==0){
                board[nx][ny]=board[cur.first][cur.second]+1;
                q.push({nx, ny});
            }
        }
    }
    int lo=0, hi=510;
    while(lo<hi){
        int mid=(lo+hi)/2+1;
        if(check(mid))
            lo=mid;
        else hi=mid-1;
        fill(&mark[0][0], &mark[509][510], 0);
    }
    cout << lo;
    return 0;
}
