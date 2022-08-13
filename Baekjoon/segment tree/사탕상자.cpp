//segment tree, binary search
#include <iostream>
#include <algorithm>
using namespace std;
int N, candy[1000010], st[4*1000010], A, B, C;
int query(int nn, int a, int b, int qa, int qb){
    if(qa<=a && b <=qb)
        return st[nn];
    if(qa>b || qb<a)
        return 0;
    int mid=(a+b)/2;
    return query(nn*2, a, mid, qa, qb)+query(nn*2+1, mid+1, b, qa, qb);
}
void update(int nn, int a, int b, int qa, int qb,int val){
    if(qa<=a && b<=qb){
        st[nn]=val;
        return;
    }
    if(qa>b || qb<a) return;
    int mid=(a+b)/2;
    update(2*nn, a, mid, qa, qb, val);
    update(2*nn+1, mid+1, b, qa, qb, val);
    st[nn]=st[nn*2]+st[nn*2+1];
}
int check(int k){
    int val=query(1, 1, 1e6, 1, k);
    if(val>=B) return 1;
    return 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for(int i=1; i<=N; i++){
        cin >> A;
        if(A==1){
            cin >> B;
            int lo=1, hi=1e6;
            while(lo<hi){
                int mid=(lo+hi)/2;
                if(check(mid))
                    hi=mid;
                else lo=mid+1;
            }
            candy[lo]--;
            update(1,1,1e6,lo,lo,candy[lo]);
            cout << lo << "\n";
        }
        else{
            cin >> B >> C;
            candy[B]+=C;
            update(1, 1, 1e6, B, B, candy[B]);
        }
    }
    return 0;
}
