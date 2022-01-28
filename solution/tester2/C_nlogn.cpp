// O(n log n) DP
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
#define INF 2000000000
using namespace std;
using P = pair<int,int>;
int n,in[M],num[M],dp[M],nxt[M];
vector<P> mx[M];
int main()
{
    while (~scanf("%d", &n)) {
        unordered_map<int,int> mp;
        REP(i,1,n) {
            int x;
            scanf("%d", &x);
            mp[x] = i;
        }
        REP(i,1,n) {
            scanf("%d", &num[i]);
            in[i] = mp[num[i]];
        }

        in[0] = -1;
        MSET(nxt, -1);
        vector<int> tmp;
        REP(i,0,n) mx[i].clear();
        for (int i=n; i>=0; i--) {
            if (!tmp.size() || tmp.back() > in[i]) {
                tmp.push_back(in[i]);
                dp[i] = tmp.size();
            } else {
                auto it = lower_bound(tmp.begin(), tmp.end(), in[i], greater<int> ());
                *it = in[i];
                dp[i] = it - tmp.begin() + 1;
            }

            int d = dp[i];
            while (mx[d].size() && num[i] >= num[mx[d].back().second]) {
                mx[d].pop_back();
            }
            mx[d].push_back(P(in[i], i));

            if (d != 1) {
                auto it = lower_bound(mx[d-1].begin(), mx[d-1].end(), P(in[i], -INF));
                nxt[i] = it->second;
            }
        }

        int p = 0;
        while (p != -1) {
            if (p != 0) printf("%d%c", num[p], dp[p]==1 ? '\n' : ' ');
            p = nxt[p];
        }
    }
    return 0;
}
