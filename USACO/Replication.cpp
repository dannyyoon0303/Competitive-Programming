//2020 USACO December Gold 1
#include <iostream>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
int N, D, bump[1010][1010], dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1}, visited[1010][1010], rad[1010][1010], value[1010][1010], cnt;
char board[1010][1010];
queue <pair<int,int>> q, sq;
struct Data{
    int x, y, val;
};
bool cmp(Data&a, Data&b){
    return a.val<b.val;
}
priority_queue<Data, vector<Data>, decltype(&cmp)> pq(&cmp);
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> D;
    for(int i=1; i<=N; i++){
        string s; cin >> s;
        for(int j=0; j<s.length(); j++){
            board[i][j+1]=s[j];
            if(s[j]=='S'){
                sq.push({i, j+1});
                rad[i][j+1]=1;
            }
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(board[i][j]=='#')
                q.push({i,j});
        }
    }
    while(!q.empty()){
        auto cur=q.front();q.pop();
        int x=cur.first, y=cur.second;
        for(int i=0; i<4; i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(1<=nx && nx<=N && 1<=ny && ny<=N){
                if(board[nx][ny]!='#' && bump[nx][ny]==0){
                    bump[nx][ny]=bump[x][y]+1;
                    q.push({nx, ny});
                }
            }
        }
    }
    while(!sq.empty()){
        auto cur=sq.front();sq.pop();
        int x=cur.first, y=cur.second;
        for(int i=0; i<4; i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(1<=nx && nx<=N && 1<=ny && ny<=N){
                if(board[nx][ny]=='.' && visited[nx][ny]==0){
                    int r=(visited[x][y]+1)/D;
                    if(r==bump[nx][ny]){
                        rad[nx][ny]=r;
                    }
                    else if(r<bump[nx][ny]){
                        rad[nx][ny]=r+1;
                        visited[nx][ny]=visited[x][y]+1;
                        sq.push({nx, ny});
                    }
                }
            }
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(rad[i][j]>0){
                value[i][j]=rad[i][j];
                pq.push({i, j, rad[i][j]});
            }
        }
    }
    while(!pq.empty()){
        auto now=pq.top(); pq.pop();
        int x=now.x, y=now.y;
        if(now.val<value[x][y]) continue;
        for(int i=0; i<4; i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(1<=nx && nx<=N && 1<=ny && ny<=N && board[nx][ny]!='#'){
                if(now.val-1 >value[nx][ny]){
                    value[nx][ny]=now.val-1;
                    pq.push({nx,ny,value[nx][ny]});
                }
            }
        }
    }
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            if(value[i][j]>0)
                cnt++;
        }
    }
    cout << cnt;
    return 0;
}
