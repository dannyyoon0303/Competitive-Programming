//https://www.acmicpc.net/problem/8068
//Modified Dijkstra
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
int N, M, board[110][110], sum, wsum, mark[110][110];
int dx[4]={1,-1,0,0}, dy[4]={0,0,1,-1};
struct Data{
    int x, y, h;
};
bool cmp(Data &a, Data&b){
    return a.h>b.h;
}
priority_queue<Data, vector<Data>, decltype(&cmp)> pq(&cmp);
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=M; j++){
            cin >> board[i][j]; sum+=board[i][j];
            if(i==1){
                pq.push({i,j,board[i][j]});
                mark[i][j]=board[i][j];
            }
            else if(i==N){
                pq.push({i,j, board[i][j]});
                mark[i][j]=board[i][j];
            }
            else if(j==1 || j==M){
                pq.push({i,j,board[i][j]});
                mark[i][j]=board[i][j];
            }
        }
    }
    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();
        int x=cur.x, y=cur.y, h=cur.h;
        wsum+=mark[x][y];
        for(int i=0; i<4; i++){
            int nx=x+dx[i], ny=y+dy[i];
            if(1<=nx && nx<=N && 1<=ny && ny<=M){
                if(mark[nx][ny]==0){
                    mark[nx][ny]=max(board[nx][ny], mark[x][y]);
                    pq.push({nx, ny, mark[nx][ny]});
                }
            }
        }
        
    }
    cout << wsum-sum;
    return 0;
}
