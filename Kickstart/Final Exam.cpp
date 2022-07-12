#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
long long T, N, M, k;
multiset <long long> s;
map <long long, long long> m;
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    for(long long l=1; l<=T;l++){
        cin >> N >> M;
        for(long long i=1; i<=N; i++){
            long long l, h;
            cin >> l >> h;
            s.insert(l);m[l]=1;
            if(m[h]!=0) m[h]=3;
            else{
                s.insert(h);m[h]=2;
            }
        }
        for(long long i=1; i<=M; i++){
            cin >> k;
            if(i==1) cout << "Case #" << l << ": ";
            //k라는 점수가 경계값으로 존재하는 경우
            if(m[k]!=0){
                cout << k << " ";
                if(m[k]==3){ s.erase(k); m[k]=0;}
                else if(m[k]==2){
                    s.erase(k);m[k]=0;
                    if(m[k-1]!=0) m[k-1]=3;
                    else{
                        s.insert(k-1);m[k-1]=2;
                    }
                }
                else{
                    s.erase(k);m[k]=0;
                    if(m[k+1]!=0) m[k+1]=3;
                    else{
                        s.insert(k+1);m[k+1]=1;
                    }
                }
            }
            else{
                auto up=s.upper_bound(k);
                if(up==s.end()){
                    up--; long long n=*up;
                    cout << n << " ";
                    if(m[n]==3){s.erase(n);m[n]=0;}
                    else if(m[n-1]!=0){
                        s.erase(n);m[n]=0;
                        m[n-1]=3;
                    }
                    else{
                        s.erase(n);m[n]=0;
                        s.insert(n-1);m[n-1]=2;
                    }
                }
                else if (up==s.begin()){
                    long long n=*up;
                    cout << n << " ";
                    if(m[n]==3){s.erase(n);m[n]=0;}
                    else if(m[n+1]!=0){
                        s.erase(n);m[n]=0;
                        m[n+1]=3;
                    }
                    else{
                        s.erase(n);m[n]=0;
                        s.insert(n+1);m[n+1]=1;
                    }
                }
                else{
                    auto lo=up; lo--;
                    if(m[*lo]==1 && m[*up]==2){
                        cout << k << " ";
                        if(m[k-1]!=0){
                            s.erase(k);m[k]=0;
                            m[k-1]=3;
                        }
                        else{
                            s.erase(k);m[k]=0;
                            s.insert(k-1);m[k-1]=2;
                        }
                        if(m[k+1]!=0){
                            s.erase(k);m[k]=0;
                            m[k+1]=3;
                        }
                        else{
                            s.erase(k);m[k]=0;
                            s.insert(k+1);m[k+1]=1;
                        }
                    }
                    else{
                        long long lp=*lo, hp=*up;
                        if(k-lp<=hp-k){
                            cout << lp << " ";
                            if(m[lp]==3){s.erase(lp);m[lp]=0;}
                            else if(m[lp-1]!=0){
                                s.erase(lp);m[lp]=0;
                                m[lp-1]=3;
                            }
                            else{
                                s.erase(lp);
                                s.insert(lp-1);m[lp-1]=m[lp];
                                m[lp]=0;
                            }
                        }
                        else{
                            cout << hp << " ";
                            if(m[hp]==3){s.erase(hp);m[hp]=0;}
                            else if(m[hp+1]!=0){
                                s.erase(hp);m[hp]=0;
                                m[hp+1]=3;
                            }
                            else{
                                s.erase(hp);
                                s.insert(hp+1);m[hp+1]=m[hp];
                                m[hp]=0;
                            }
                        }
                    }
                }
            }
        }
        s.clear();m.clear();
        cout << "\n";
    }
    return 0;
}
