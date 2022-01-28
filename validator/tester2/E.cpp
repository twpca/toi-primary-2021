#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N[] = {500, 20, 70, 70, 500};
constexpr int MN_A = 0;
constexpr int MX_A[] = {2'000'000, 1, 1, 2'000'000, 2'000'000};
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

    int n = inf.readInt(MN_N, MX_N[s]);
    inf.readChar('\n');
    REP(i,1,n) REP(j,1,n) {
        inf.readInt(MN_A, MX_A[s]);
        if (j==n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    inf.readEof();
    return 0;
}
