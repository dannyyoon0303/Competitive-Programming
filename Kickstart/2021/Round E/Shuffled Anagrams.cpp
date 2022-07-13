#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>
using namespace std;
int T;
vector <int> v[26], l;
vector <pair<int,int>> k;
map<int, int> m;
int main(){
    cin >> T;
    for(int i=1; i<=T; i++){
        int ans[10010];
        string s;
        cin >> s;
        for(int i=0; i<s.length(); i++){
            m[s[i]-'a']++;
            v[s[i]-'a'].push_back(i);
        }
        for(int i=0; i<26; i++){
            if(m[i]!=0)
                k.push_back({m[i], i});
        }
        sort(k.begin(),k.end());
        if(k[k.size()-1].first >s.length()/2)
            cout << "Case #" << i << ": IMPOSSIBLE\n";
        else{
            for(int i=(int)k.size()-2; i>=0; i--){
                for(int j=0; j<v[k[i].second].size(); j++)
                    l.push_back(v[k[i].second][j]);
            }
            int n=(int)k.size()-1;
            for(int j=0; j<v[k[n].second].size(); j++)
                l.push_back(v[k[n].second][j]);
            int ind=0;
            for(int i=(int)k.size()-1; i>=0; i--){
                int abt=k[i].second, it=k[i].first;
                for(int i=1; i<=it; i++){
                    ans[l[ind]]=abt;
                    ind++;
                }
            }
            cout << "Case #" << i << ": ";
            for(int i=0; i<s.length(); i++){
                char c='a'+ans[i];
                cout << c;
            }
            cout << "\n";
        }
        for(int i=0; i<26; i++)v[i].clear();
        l.clear();k.clear();m.clear();
    }
    return 0;
}
