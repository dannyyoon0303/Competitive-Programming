#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
long long T, R, C, board[310][310], ans, mark[310][310];
long long dx[4]={0,0,1,-1}, dy[4]={1,-1,0,0};
set <pair<long long, pair<long long,long long>>> s;
int main(){
    cin >> T;
    for(long long i=1; i<=T; i++){
        cin >> R >> C;
        for(long long i=1; i<=R; i++){
            for(long long j=1; j<=C; j++){
                cin >> board[i][j];
                s.insert({board[i][j], {i,j}});
            }
        }
        while(s.size()>0){
            auto it=s.end(); it--;
            auto cur=*it;long long val=cur.first; auto loc=cur.second;
            mark[loc.first][loc.second]=1;
            for(long long i=0; i<4; i++){
                long long nx=loc.first+dx[i], ny=loc.second+dy[i];
                if(1<=nx && nx<=R && 1<=ny && ny<=C && mark[nx][ny]==0){
                    if(val-1>board[nx][ny]){
                        ans+=val-board[nx][ny]-1;
                        s.erase({board[nx][ny], {nx, ny}});
                        board[nx][ny]=val-1;
                        s.insert({val-1, {nx, ny}});
                    }
                }
            }
            s.erase(*it);
        }
        cout << "Case #" << i << ": " << ans << "\n";
        ans=0;
        fill(&mark[0][0], &mark[309][310], 0);
    }
    return 0;
}
