// Costflow: nm
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;
using T = tuple<int,int,int>;
struct Costflow {
    const static int INF = 2000000000;
    struct Edge {
        int s, t, r, cost, opp;
        Edge () {}
        Edge (int _s, int _t, int _r, int _cost, int _opp) {
            s = _s;
            t = _t;
            r = _r;
            cost = _cost;
            opp = _opp;
        }
    };

    int n, st, ed;
    vector<int> dis, pre, rec, p;
    vector<bool> inq, vis;
    vector<vector<Edge>> e;

    Costflow() {}
    Costflow(int _n, int, int _st, int _ed) {
        n = _n;
        dis = vector<int> (n+1);
        pre = vector<int> (n+1);
        rec = vector<int> (n+1);
        p = vector<int> (n+1);
        inq = vector<bool> (n+1);
        vis = vector<bool> (n+1);
        e = vector<vector<Edge>> (n+1);

        st = _st;
        ed = _ed;
    }
    void add(int x,int y,int r,int c) {
        e[x].emplace_back(x, y, r, c, e[y].size());
        e[y].emplace_back(y, x, 0, -c, e[x].size()-1);
    }
    bool spfa() {
        deque<int> q;
        fill(inq.begin(), inq.end(), false);
        fill(dis.begin(), dis.end(), -INF);

        dis[st] = 0;
        q.push_back(st);
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            inq[cur] = false;

            for (int i=0; i<(int)e[cur].size(); ++i)
                if (e[cur][i].r > 0 && dis[cur] + e[cur][i].cost > dis[e[cur][i].t]) {
                    dis[e[cur][i].t] = dis[cur] + e[cur][i].cost;
                    pre[e[cur][i].t] = cur;
                    rec[e[cur][i].t] = i;
                    if (!inq[e[cur][i].t]) {
                        inq[e[cur][i].t] = true;
                        if (rand()%2) {
                            q.push_back(e[cur][i].t);
                        } else {
                            q.push_front(e[cur][i].t);
                        }
                    }
                }
        }
        return dis[ed] != -INF;
    }
    bool dijk() {
        fill(dis.begin(), dis.end(), -INF);
        fill(vis.begin(), vis.end(), false);

        dis[st] = 0;
        while (true) {
            int cur=-1, d=-INF;
            REP(i,0,n) if (!vis[i] && dis[i] > d) {
                d = dis[i];
                cur = i;
            }
            if (cur == -1) break;
            vis[cur] = true;

            for (int i=0; i<(int)e[cur].size(); ++i) {
                int adj = p[cur] - p[e[cur][i].t];
                if (e[cur][i].r > 0 && dis[cur] + e[cur][i].cost + adj > dis[e[cur][i].t]) {
                    dis[e[cur][i].t] = dis[cur] + e[cur][i].cost + adj;
                    pre[e[cur][i].t] = cur;
                    rec[e[cur][i].t] = i;
                }
            }
        }
        return dis[ed] != -INF;
    }
    int costflow() {
        calc_potential();

        int delta, maxflow=0, mincost=0;
        while (dijk()) {
            delta = INF;
            for (int i=ed; i!=st; i=pre[i]) {
                delta = min(delta, e[pre[i]][rec[i]].r);
            }
            for (int i=ed; i!=st; i=pre[i]) {
                e[pre[i]][rec[i]].r -= delta;
                e[i][e[pre[i]][rec[i]].opp].r += delta;
            }
            mincost += (dis[ed] - p[st] + p[ed]) * delta;
            maxflow += delta;

            // update
            REP(i,0,n) if (dis[i]!=-INF) p[i] += dis[i];
        }
        return mincost;
    }
    void calc_potential() {
        spfa();
        REP(i,0,n) p[i] = dis[i];
    }
}cf;
void init() {
    int n;
    scanf("%d", &n);
    cf = Costflow(2*n+2, n*n*2 + 4*n + 50, 0, 2*n+1);

    REP(i,1,n) REP(j,1,n) {
        int x;
        scanf("%d", &x);
        cf.add(i, j+n, 1, x);
    }
    REP(i,1,n) cf.add(0, i, 1, 0);
    REP(i,n+1,2*n) cf.add(i, 2*n+1, 1, 0);
    printf("%d\n", cf.costflow());
    REP(i,1,n) printf("%d%c", -cf.p[i], i==n ? '\n' : ' ');
    REP(i,1,n) printf("%d%c", cf.p[i+n], i==n ? '\n' : ' ');
}
int main()
{
    srand(114514);
    init();
    return 0;
}
