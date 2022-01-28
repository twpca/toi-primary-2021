#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 2;
constexpr int MX_N[] = {50'000, 500, 50'000, 50'000, 50'000};
constexpr int MN_Q = 1;
constexpr int MX_Q = 200'000;

constexpr int MN_W = 1;
constexpr int MX_W = 1000;
constexpr int MN_P = 1;
constexpr int MX_P[] = {6, 6, 1, 6, 6};

constexpr int MN_H = 0;
constexpr int MX_H = 23;
constexpr int MN_M = 0;
constexpr int MX_M = 59;

vector<int> e[MX_N[0] + 100];
bool vis[MX_N[0] + 100];

int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
void dfs(int cur) {
    vis[cur] = true;
    for (int i: e[cur]) if (!vis[i]) {
        dfs(i);
    }
}
void is_tree(int n) {
    MSET(vis, false);
    dfs(1);
    ensuref(accumulate(vis+1, vis+n+1, 0) == n, "not a tree");
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int n = inf.readInt(MN_N, MX_N[s]);
    inf.readChar(' ');
    int q = inf.readInt(MN_Q, MX_Q);
    inf.readChar('\n');

    REP(i,1,n-1) {
        // u v w a b p
        int u = inf.readInt(1, n);
        inf.readChar(' ');
        int v = inf.readInt(1, n);
        inf.readChar(' ');
        inf.readInt(MN_W, MX_W);
        inf.readChar(' ');

        int a = inf.readInt(0, MX_P[s]-1);
        inf.readChar(' ');
        int b = inf.readInt(0, MX_P[s]-1);
        inf.readChar(' ');
        int p = inf.readInt(MN_P, MX_P[s]);
        inf.readChar('\n');

        ensuref(a<=p-1, "a <= p-1");
        ensuref(b<=p-1, "a <= p-1");
        e[u].push_back(v);
        e[v].push_back(u);

        if (s==3) {
            ensuref(u==i, "u==i");
            ensuref(v==i+1, "v==i+1");
        }
    }

    REP(i,1,q) {
        // h m s t
        inf.readInt(MN_H, MX_H);
        inf.readChar(' ');
        inf.readInt(MN_M, MX_M);
        inf.readChar(' ');

        int ss = inf.readInt(1, n);
        inf.readChar(' ');
        int tt = inf.readInt(1, n);
        inf.readChar('\n');

        ensuref(ss!=tt, "s != t");
    }
    inf.readEof();

    is_tree(n);
    return 0;
}
