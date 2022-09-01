//USACO 2017 Jan Gold 3
#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;
const int INF=1e9;
int N, board[25][25], visited[25][25][4][25][25][4];
int dx[4]={-1,0,1,0}, dy[4]={0,1,0,-1}, dd[2]={-1,1};
struct Data{
    int x1, y1, d1, x2, y2, d2;
};
queue<Data> q;
int check(int x, int y){
    if(1<=x && x<=N && 1<=y && y<=N && board[x][y]==1)
        return 1;
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=N; i>=1; i--){
        string s; cin >> s;
        for(int j=0; j<N; j++){
            if(s[j]=='E'){
                board[i][j+1]=1;
            }
            else board[i][j+1]=0;
        }
    }
    fill(&visited[0][0][0][0][0][0], &visited[24][24][3][24][24][4], INF);
    q.push({1,1,1,1,1,2});
    visited[1][1][1][1][1][2]=0;
    while(!q.empty()){
        auto cur=q.front(); q.pop();
        int x1=cur.x1, y1=cur.y1, d1=cur.d1, x2=cur.x2, y2=cur.y2, d2=cur.d2;
        if(x1==N && y1==N && x2==N && y2==N){
            cout << visited[x1][y1][d1][x2][y2][d2]; break;
        }
        int nx1, ny1, nx2, ny2;
        if(x1==N && y1==N){
            nx1=N; ny1=N;
        }
        else{
            nx1=x1+dx[d1]; ny1=y1+dy[d1];
        }
        if(x2==N && y2==N){
            nx2=N; ny2=N;
        }
        else{
            nx2=x2+dx[d2]; ny2=y2+dy[d2];
        }
        //forward movement
        if(!check(nx1, ny1)){
            nx1=x1; ny1=y1;
        }
        if(!check(nx2, ny2)){
            nx2=x2; ny2=y2;
        }
        if(visited[x1][y1][d1][x2][y2][d2]+1<visited[nx1][ny1][d1][nx2][ny2][d2]){
            visited[nx1][ny1][d1][nx2][ny2][d2]=visited[x1][y1][d1][x2][y2][d2]+1;
            q.push({nx1, ny1, d1, nx2, ny2, d2});
        }
        //change direction
        int nd1, nd2;
        for(int i=0; i<2; i++){
            nd1=(d1+dd[i]+4)%4;nd2=(d2+dd[i]+4)%4;
            if(visited[x1][y1][d1][x2][y2][d2]+1<visited[x1][y1][nd1][x2][y2][nd2]){
                visited[x1][y1][nd1][x2][y2][nd2]=visited[x1][y1][d1][x2][y2][d2]+1;
                q.push({x1, y1, nd1, x2, y2, nd2});
            }
        }
    }
    
    return 0;
}
