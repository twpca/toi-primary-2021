// pick any dust > 0
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 1005
using namespace std;
using LL = long long;
constexpr LL INF = (1LL << 61);
int n,m;
int s[M],d[M];
LL t[M], ans;

int main()
{
    while (~scanf("%d %d", &n, &m)) {
        REP(i,2,n) {
            int x;
            scanf("%d", &x);
            t[i] = t[i-1] + x;
        }
        REP(i,1,n) scanf("%d", &s[i]);
        REP(i,1,n) scanf("%d", &d[i]);

        LL tmp = 0;
        ans = 0;
        REP(i,1,n) if (d[i]) {
            tmp = s[i] + (s[i] % d[i]);
            tmp *= (s[i]/d[i] + 1) / 2LL;
            ans = max(ans, tmp);
        }
        REP(i,1,n) if (!d[i]) {
            LL rm = m - t[i];
            ans = max(ans, (LL)s[i] * rm);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
