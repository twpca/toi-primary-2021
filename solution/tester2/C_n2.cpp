// O(n^2) DP
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 200005
#define INF 2000000000
using namespace std;
using P = pair<int,int>;
int n,a[M],b[M],w[M],dp[M],nxt[M];
int main()
{
    while (~scanf("%d", &n)) {
        unordered_map<int,int> mp;
        REP(i,1,n) scanf("%d", &a[i]);
        REP(i,1,n) {
            scanf("%d", &b[i]);
            mp[b[i]] = i;
        }
        REP(i,1,n) w[i] = mp[a[i]];

        for (int i=n; i>=1; i--) {
            dp[i] = 1;
            nxt[i] = -1;
            for (int j=i+1; j<=n; j++) if (w[j] > w[i]) {
                if (dp[j] == dp[i]-1 && a[j] > a[nxt[i]]) {
                    nxt[i] = j;
                } else if (dp[j]+1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    nxt[i] = j;
                }
            }
        }

        int k = *max_element(dp+1, dp+n+1);
        int p = 0;
        REP(i,1,n) if (dp[i]==k) {
            if (!p || a[p] < a[i]) p = i;
        }

        while (p != -1) {
            printf("%d%c", a[p], dp[p]==1 ? '\n' : ' ');
            p = nxt[p];
        }
    }
    return 0;
}
