// O(n log n)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M 50005
using namespace std;
using P = pair<int,int>;
struct Edge {
    int t, w, a, b, p;
    Edge () {}
    Edge (int _t, int _w, int _a, int _b, int _p) noexcept:
        t(_t), w(_w), a(_a), b(_b), p(_p) {}
};
int n,q,dep[M],hop[M];
int fa[M][16],up[M][60][16],down[M][60][16];

vector<Edge> e[M];
int next_train(int t,int p,int a) {
    int res = t/p*p + a;
    if (res < t) res += p;
    return res;
}
int lca(int x,int y) {
    if (hop[x] < hop[y]) swap(x, y);
    int diff = hop[x] - hop[y];
    REP(i,0,15) if (diff & (1<<i)) {
        x = fa[x][i];
    }
    if (x==y) return x;

    for (int i=15; i>=0; i--) {
        if (fa[x][i] != fa[y][i]) {
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
int goup(int cur,int m,int d) {
    int res = 0;
    for (int i=15; i>=0; i--) if ((1<<i) & d) {
        if (res != 0) res++;
        res += up[cur][(m+res)%60][i];
        cur = fa[cur][i];
    }
    return res;
}
int godw(int cur,int m,int d) {
    int res = 0;
    vector<pair<int,int>> p;
    for (int i=15; i>=0; i--) if ((1<<i) & d) {
        p.push_back(P(cur, i));
        cur = fa[cur][i];
    }

    reverse(p.begin(), p.end());
    for (auto i: p) {
        if (res != 0) res++;
        res += down[i.first][(m+res)%60][i.second];
    }
    return res;
}
void dfs(int cur,int f,int d,int h,Edge ef) {
    dep[cur] = d;
    hop[cur] = h;
    fa[cur][0] = f;

    if (f!=-1) {
        int p = ef.p;
        REP(i,0,59) {
            int st = next_train(i, p, ef.b);
            up[cur][i][0] = st + ef.w - i;
        }
        REP(i,0,59) {
            int st = next_train(i, p, ef.a);
            down[cur][i][0] = st + ef.w - i;
        }
    }

    for (auto i: e[cur]) if (dep[i.t] == -1) {
        dfs(i.t, cur, d + i.w, h+1, i);
    }
}
void init() {
    int x, y, z, a, b, p;
    REP(i,1,n) e[i].clear();
    REP(i,1,n-1) {
        scanf("%d %d %d %d %d %d", &x, &y, &z, &a, &b, &p);
        e[x].push_back(Edge(y, z, a, b, p));
        e[y].push_back(Edge(x, z, b, a, p));
    }

    MSET(up, -1);
    MSET(down, -1);
    fill(dep, dep+n+1, -1);
    dfs(1, -1, 0, 0, Edge());
    REP(j,1,15) REP(i,1,n) {
        if (fa[i][j-1] == -1) {
            fa[i][j] = -1;
        } else {
            fa[i][j] = fa[fa[i][j-1]][j-1];
        }
    }

    REP(k,1,15) REP(i,1,n) if(fa[i][k-1] != -1) REP(j,0,59) {
        z = fa[i][k-1];
        int tmp = up[i][j][k-1];
        up[i][j][k] = tmp + 1 + up[z][(j+tmp+1)%60][k-1];
    }
    REP(k,1,15) REP(i,1,n) if(fa[i][k-1] != -1) REP(j,0,59) {
        z = fa[i][k-1];
        int tmp = down[z][j][k-1];
        down[i][j][k] = tmp + 1 + down[i][(j+tmp+1)%60][k-1];
    }
}
void work() {
    int h, m, x, y;
    REP(i,1,q) {
        scanf("%d %d %d %d", &h, &m, &x, &y);
        int z = lca(x, y);
        if (x==z) {
            printf("%d\n", godw(y, m, hop[y]-hop[x]));
        } else {
            int ans = goup(x, m, hop[x]-hop[z]);
            if (y != z) {
                ans++;
                ans += godw(y, (m+ans)%60, hop[y]-hop[z]);
            }
            printf("%d\n", ans);
        }
    }
}
int main()
{
    while (~scanf("%d %d", &n, &q)) {
        init();
        work();
    }
    return 0;
}
