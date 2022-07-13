#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int T;
int main(){
    cin >> T;
    for(int i=1; i<=T; i++){
        string N, ans;
        cin >> N;int s=0;
        for(int i=0; i<N.length(); i++){
            s+=N[i]-'0';
            s%=9;
        }
        if(s%9==0){
            int ind=0;
            for(int i=1; i<N.length(); i++){
                if(N[i]-'0'>0){
                    ind=i;break;
                }
            }
            if(ind==0) ans=N+'0';
            else ans=N.substr(0, ind)+'0'+N.substr(ind, N.length()-ind);
        }
        else{
            int ind=0, insert=9-s, cnt=0;
            for(int i=0; i<N.length(); i++){
                if(N[i]-'0'>insert){
                    cnt++;
                    ind=i; break;
                }
            }
            if(cnt==0) ans=N+to_string(insert);
            else ans=N.substr(0, ind)+to_string(insert)+N.substr(ind, N.length()-ind);
        }
        cout << "Case #" << i << ": " << ans << "\n";
    }
    return 0;
}

