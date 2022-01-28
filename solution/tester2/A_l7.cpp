// subtask 1
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 1005
using namespace std;
int n,in[M];
int cb(int x) {
    int res = 0;
    if (x&1) res++;
    if (x&2) res++;
    if (x&4) res++;
    return res;
}
int main()
{
    while (~scanf("%d", &n)) {
        REP(i,1,n) scanf("%d", &in[i]);
        stable_sort(in+1, in+n+1, [](int x,int y) {
            return cb(x) < cb(y);
        });
        REP(i,1,n) printf("%d%c", in[i], i==n ? '\n' : ' ');
    }
    return 0;
}
