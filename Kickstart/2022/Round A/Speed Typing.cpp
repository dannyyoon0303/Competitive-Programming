#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int T;
int main(){
    cin >> T;
    for(int i=1; i<=T; i++){
        string I, P;int cnt=0, Idex=0, Pdex=0;
        cin >> I >> P;
        
        int Il=I.length(), Pl=P.length();
        while(Pdex < Pl){
            if(Idex==Il){
                cnt+=(Pl-Pdex);
                break;
            }
            if(P[Pdex]==I[Idex]){
                Idex++;Pdex++;
            }
            else{
                Pdex++;cnt++;
            }
        }
        if(Idex==Il)
            cout << "Case #" << i << ": " << cnt << "\n";
        else
            cout << "Case #" << i << ": IMPOSSIBLE" << "\n";
    }
    return 0;
}
