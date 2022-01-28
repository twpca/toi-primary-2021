// O(n^2 log(S))
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

// all >= x
bool check(int ed, int x) {
    LL res = 0;
    REP(i,1,ed) {
        if (d[i] == 0) {
            if (s[i] >= x) return INF;
            continue;
        }

        if (s[i] >= x) {
            res += (s[i] - x) / d[i] + 1;
        }
    }
    return res >= m - t[ed];
}
LL calc_sum(int ed,int x,int mxcnt,bool flg=false) {
    LL res = 0;
    LL cnt = 0;
    LL cmn = 0;
    REP(i,1,ed) {
        if (s[i] > x) {
            int mx = s[i];
            int mn = s[i] - (s[i] - x) / d[i] * d[i];
            // assert(d[i] != 0);
            if (mn == x) {
                mn += d[i];
                cmn++;
            }
            int c = (mx-mn) / d[i] + 1;
            res += (LL)(mx+mn) * c / 2LL;
            cnt += c;
        }
        if (s[i] == x) {
            if (d[i] != 0) cmn++;
            else cmn = INF;
        }
    }

    // runtime error if
    // cnt < mxcnt < cnt+cmn
    if (flg) {
        assert(!( cmn<INF && cnt < mxcnt && mxcnt < cnt+cmn ));
    }

    res += min((LL)cmn, mxcnt-cnt) * x;
    return res;
}
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

        int edd = 1;
        int okk = -1;

        ans = 0;
        REP(ed, 1, n) {
            if (t[ed] > m) continue;

            int ok=0, ng=1000000000 + 5, mid;
            while (abs(ok-ng) > 1) {
                mid = (ok + ng) / 2;
                if (check(ed, mid)) ok = mid;
                else ng = mid;
            }
            ans = max(ans, calc_sum(ed, ok, m-t[ed]));
            if (ans == calc_sum(ed, ok, m-t[ed])) {
                edd = ed;
                okk = ok;
            }
        }

        calc_sum(edd, okk, m-t[edd], true);
        printf("%lld\n", ans);
    }
    return 0;
}
