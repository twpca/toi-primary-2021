// O(2^n * n^2)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 22
#define B(x) (1<<(x))
using namespace std;
int n,fr,cur,msk;
int in[M][M],dp[2][1<<M],mx[M];
int main()
{
    while (~scanf("%d", &n)) {
        fr = 0;
        cur = 1;
        msk = (1<<n) - 1;
        MSET(dp, 0);

        REP(i,1,n) REP(j,1,n) scanf("%d", &in[i][j]);

        REP(i,1,n) {
            REP(j,0,msk) REP(k,1,n) if (j & B(k-1)) {
                dp[cur][j] = max(dp[cur][j], dp[fr][j ^ B(k-1)] + in[i][k]);
            }

            swap(fr, cur);
            MSET(dp[cur], 0);
        }
        printf("%d\n", *max_element(dp[fr], dp[fr]+msk+1));
        REP(i,1,n) printf("%d%c", 0, i==n ? '\n' : ' ');
        REP(i,1,n) printf("%d%c", 0, i==n ? '\n' : ' ');
    }
    return 0;
}
