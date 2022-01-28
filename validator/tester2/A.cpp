#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N = 1;
constexpr int MX_N = 1000;
constexpr int MN_A[] = {1, 1, 1};
constexpr int MX_A[] = {1024, 7, 1024};
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
    vector<int> in;
    inf.readChar('\n');
    REP(i,1,n) {
        int x = inf.readInt(MN_A[s], MX_A[s]);
        in.push_back(x);
        if (i==n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    inf.readEof();

    sort(in.begin(), in.end());
    in.resize(unique(in.begin(), in.end()) - in.begin());
    ensuref(in.size()==n, "distinct numbers != n");
    return 0;
}
