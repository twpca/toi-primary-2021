#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N = 1000;
constexpr int MN_M = 1;
constexpr int MX_M[] = {1'000'000'000, 1000, 1'000'000'000};
constexpr int MN_S = 1;
constexpr int MX_S = 1'000'000'000;
constexpr int MN_D = 0;
constexpr int MX_D = 1'000'000'000;
constexpr int MN_T = 0;
constexpr int MX_T = 1'000'000'000;
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    int n = inf.readInt(MN_N, MX_N);
    inf.readChar(' ');
    int m = inf.readInt(MN_M, MX_M[s]);
    inf.readChar('\n');

    REP(i,1,n-1) {
        inf.readInt(MN_T, MX_T);
        if (i==n-1) inf.readChar('\n');
        else inf.readChar(' ');
    }
    if (n==1) inf.readChar('\n'); // empty line if n==1

    REP(i,1,n) {
        inf.readInt(MN_S, MX_S);
        if (i==n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    REP(i,1,n) {
        inf.readInt(MN_D, MX_D);
        if (i==n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    inf.readEof();
    return 0;
}
