// O(nm log(n))
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 1005
using namespace std;
using LL = long long;
using P = pair<int,int>;
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

        ans = 0;
        REP(ed, 1, n) {
            priority_queue<P> q;
            REP(i,1,ed) q.push(P(s[i], i));

            LL cnt = m - t[ed];
            LL sum = 0;
            while (cnt > 0 && !q.empty()) {
                int sc, id;
                tie(sc, id) = q.top();
                q.pop();

                sum += sc;
                cnt --;
                if (sc-d[id] > 0) {
                    q.push(P(sc-d[id], id));
                }
            }
            ans = max(ans, sum);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
