#include <iostream>
#include <algorithm>
using namespace std;
int T, R, C, board[1010][1010];
pair<int,int> h[1010][1010], v[1010][1010];
//left, right & top, down
int main(){
    cin >> T;
    for(int i=1; i<=T; i++){
        int ans=0;
        cin >> R >> C;
        for(int i=1; i<=R; i++)
            for(int j=1; j<=C; j++)
                cin >> board[i][j];
        for(int i=1; i<=R; i++){
            int prev=0;
            for(int j=1; j<=C; j++){
                if(board[i][j]==0) continue;
                else if (board[i][j-1]==0){
                    prev=j;
                    h[i][j].first=1;
                }
                else h[i][j].first=j-prev+1;
            }
            for(int j=C; j>=1; j--){
                if(board[i][j]==0) continue;
                else if (board[i][j+1]==0){
                    prev=j;
                    h[i][j].second=0;
                }
                else h[i][j].second=prev-j+1;
            }
        }
        for(int i=1; i<=C; i++){
            int prev=0;
            for(int j=1; j<=R; j++){
                if(board[j][i]==0) continue;
                else if (board[j-1][i]==0){
                    prev=j;
                    v[j][i].first=1;
                }
                else v[j][i].first=j-prev+1;
            }
            for(int j=R; j>=1; j--){
                if(board[j][i]==0) continue;
                else if (board[j+1][i]==0){
                    prev=j;
                    v[j][i].second=0;
                }
                else v[j][i].second=prev-j+1;
            }
        }
        for(int i=1; i<=R; i++){
            for(int j=1; j<=C; j++){
                if(board[i][j]==1){
                    int l=h[i][j].first, r=h[i][j].second, t=v[i][j].first, d=v[i][j].second;
                    if(l>=2){
                        if(t>=2){
                            if(l>=4) ans+=min(l/2-1, t-1);
                            if(t>=4) ans+=min(t/2-1, l-1);
                        }
                        if(d>=2){
                            if(l>=4) ans+=min(l/2-1, d-1);
                            if(d>=4) ans+=min(d/2-1, l-1);
                        }
                    }
                    if(r>=2){
                        if(t>=2){
                            if(r>=4) ans+=min(r/2-1, t-1);
                            if(t>=4) ans+=min(t/2-1, r-1);
                        }
                        if(d>=2){
                            if(r>=4) ans+=min(r/2-1, d-1);
                            if(d>=4) ans+=min(d/2-1, r-1);
                        }
                    }
                }
            }
        }
        cout << "Case #" << i << ": " << ans << "\n";
        fill(&board[0][0], &board[1009][1010], 0);
    }
    return 0;
}
