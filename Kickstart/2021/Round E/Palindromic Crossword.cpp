#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
int T, N, M, mark[1010][1010],filled;
//0 can be filled, 1 blocks
pair <int,int> sym[1010][1010];
char board[1010][1010], ans[1010][1010];
void dfs(pair<int,int> loc, char c){
    int x=loc.first, y=loc.second;
    if(board[x][y]=='.') filled++;
    ans[x][y]=c;mark[x][y]=1;
    if(sym[x][y].first>0){
        int ny=sym[x][y].first-y;
        if(mark[x][ny]==0)
            dfs({x, ny}, c);
    }
    if(sym[x][y].second>0){
        int nx=sym[x][y].second-x;
        if(mark[nx][y]==0)
            dfs({nx, y}, c);
    }
}
int main(){
    cin >> T;
    for(int i=1; i<=T; i++){
        cin >> N >> M;
        fill(&ans[1][1], &ans[N][M+1], '.');
        fill(&mark[0][0], &mark[1009][1010], 0);
        filled=0;
        for(int i=1; i<=N; i++)
            for(int j=1; j<=M; j++) sym[i][j]={0,0};
        for(int i=1; i<=N; i++){
            string s;cin >> s;s='0'+s;
            for(int j=1; j<=M; j++){
                board[i][j]=s[j];
            }
        }
        for(int i=1; i<=N; i++){
            int s=0, e;
            if(board[i][1]!='#') s=1;
            for(int j=2; j<=M; j++){
                if(board[i][j]=='#' && board[i][j-1]!='#'){
                    e=j-1;
                    for(int k=s; k<=e; k++)
                        sym[i][k].first=s+e;
                }
                if(board[i][j]!='#' && board[i][j-1]=='#')
                    s=j;
                if(j==M && board[i][j]!='#'){
                    e=j;
                    for(int k=s; k<=e; k++)
                        sym[i][k].first=s+e;
                }
            }
        }
        for(int i=1; i<=M; i++){
            int s=0, e;
            if(board[1][i]!='#') s=1;
            for(int j=2; j<=N; j++){
                if(board[j][i]=='#' && board[j-1][i]!='#'){
                    e=j-1;
                    for(int k=s; k<=e; k++)
                        sym[k][i].second=s+e;
                }
                if(board[j][i]!='#' && board[j-1][i]=='#')
                    s=j;
                if(j==N && board[j][i]!='#'){
                    e=j;
                    for(int k=s; k<=e; k++)
                        sym[k][i].second=s+e;
                }
            }
        }
        
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if(board[i][j]!='.' && board[i][j]!='#'){
                    char c=board[i][j];
                    if(mark[i][j]==0) dfs({i,j},c);
                }
            }
        }
        cout << "Case #" << i << ": " << filled << "\n";
        for(int i=1; i<=N; i++){
            for(int j=1; j<=M; j++){
                if(board[i][j]=='#') cout << board[i][j];
                else cout << ans[i][j];
            }
            cout << "\n";
        }
        
    }
    return 0;
}
