// Costflow: TLE?
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define M
using namespace std;
struct Costflow {
    const static int INF = 2000000000;
    struct Edge {
        int t, r, cost, next, opp;
        Edge () {}
        Edge (int _t, int _r, int _cost, int _next, int _opp) {
            t = _t;
            r = _r;
            cost = _cost;
            next = _next;
            opp = _opp;
        }
    };

    int n, ec, st, ed;
    vector<int> first, dis, pre, rec;
    vector<bool> inq;
    vector<Edge> e;

    Costflow() {}
    Costflow(int _n, int _m, int _st, int _ed) {
        n = _n + 1;
        ec = 0;
        first = vector<int> (n, -1);
        dis = vector<int> (n);
        pre = vector<int> (n);
        rec = vector<int> (n);
        inq = vector<bool> (n);
        e = vector<Edge> (_m);

        st = _st;
        ed = _ed;
    }
    void add(int x,int y,int r,int c) {
        e[ec] = Edge(y, r, c, first[x], ec+1);
        first[x] = ec++;
        e[ec] = Edge(x, 0, -c, first[y], ec-1);
        first[y] = ec++;
    }
    bool spfa(int _st = -1) {
        if (_st == -1) _st = st;
        deque<int> q;
        fill(inq.begin(), inq.end(), false);
        fill(dis.begin(), dis.end(), -INF);

        dis[_st] = 0;
        q.push_back(_st);
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            inq[cur] = false;

            for (int i=first[cur]; ~i; i=e[i].next)
                if (e[i].r > 0 && dis[cur] + e[i].cost > dis[e[i].t]) {
                    dis[e[i].t] = dis[cur] + e[i].cost;
                    pre[e[i].t] = cur;
                    rec[e[i].t] = i;
                    if (!inq[e[i].t]) {
                        inq[e[i].t] = true;
                        if (rand()%2) {
                            q.push_back(e[i].t);
                        } else {
                            q.push_front(e[i].t);
                        }
                    }
                }
        }
        return dis[ed] != -INF;
    }
    int costflow() {
        int delta, maxflow=0, mincost=0;
        while (spfa()) {
            delta = INF;
            for (int i=ed; i!=st; i=pre[i]) {
                delta = min(delta, e[rec[i]].r);
            }
            for (int i=ed; i!=st; i=pre[i]) {
                e[rec[i]].r -= delta;
                e[e[rec[i]].opp].r += delta;
            }
            mincost += dis[ed] * delta;
            maxflow += delta;
        }
        return mincost;
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

    cf.spfa(2*n+1);
    REP(i,1,n) printf("%d%c", -cf.dis[i], i==n ? '\n' : ' ');
    REP(i,1,n) printf("%d%c", cf.dis[i+n], i==n ? '\n' : ' ');
}
int main()
{
    srand(114514);
    init();
    return 0;
}
