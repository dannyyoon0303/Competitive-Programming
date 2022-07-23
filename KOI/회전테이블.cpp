/*KOI 2012 고등부 3번
dp reducing conditions*/
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
int N, food[3][110], dp[110][110][110][3], l[3];
//dp[i][j][k][w]: 마지막으로 먹은 음식이 각각 i,j,k, 끝점이 w의 식사일 때 회전 최소개수
int dist(int i, int j){
    return min(abs(i-j), N-abs(i-j));
}
int solve(int i, int j, int k, int w){
    int &r=dp[i][j][k][w];
    if(i==l[0] && j==l[1] && k==l[2]) r=0;
    if(r!=-1) return r;
    else{
        int start, s;
        if(w==0) start=food[0][i];
        else if(w==1) start=food[1][j];
        else start=food[2][k];
        int v1=1e9, v2=1e9, v3=1e9;
        if(i+1<=l[0]){
            if(w==0) s=start;
            else if(w==1){
                s=(start+2*N/3)%N; if(s==0) s=N;
            }
            else{
                s=(start+N/3)%N; if(s==0) s=N;
            }
            v1=dist(s, food[0][i+1])+solve(i+1, j, k, 0);
        }
        if(j+1<=l[1]){
            if(w==1) s=start;
            else if(w==2){
                s=(start+2*N/3)%N; if(s==0) s=N;
            }
            else{
                s=(start+N/3)%N; if(s==0) s=N;
            }
            v2=dist(s, food[1][j+1])+solve(i, j+1, k, 1);
        }
        if(k+1<=l[2]){
            if(w==2) s=start;
            else if(w==0){
                s=(start+2*N/3)%N; if(s==0) s=N;
            }
            else{
                s=(start+N/3)%N; if(s==0) s=N;
            }
            v3=dist(s, food[2][k+1])+solve(i, j, k+1, 2);
        }
        r=min(v1, min(v2, v3));
    }
    return r;
}
int main(){
    int ans=1e9;
    cin >> N;
    for(int i=0; i<3; i++){
        cin >> l[i];
        for(int j=1; j<=l[i]; j++) cin >> food[i][j];
    }
    fill(&dp[0][0][0][0], &dp[109][109][109][3],-1);
    food[0][0]=1;food[1][0]=1+N/3;food[2][0]=1+2*N/3;
    ans=min(ans, dist(food[0][0], food[0][1])+solve(1,0,0,0));
    ans=min(ans, dist(food[1][0], food[1][1])+solve(0,1,0,1));
    ans=min(ans, dist(food[2][0], food[2][1])+solve(0,0,1,2));
    cout << ans;
    return 0;
}
