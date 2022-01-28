#include<bits/stdc++.h>
#include "testlib.h"
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
using namespace std;
constexpr int MN_N[] = {1, 1, 1, 1};
constexpr int MX_N[] = {200000, 10, 100, 200000};
constexpr int MN_AB = 0;
constexpr int MX_AB = 1000000000;
int n;
vector<int> a,b;
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
bool same_permutation() {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a.size()!=n || b.size()!=n) return false;
    REP(i,0,n-1) if (a[i] != b[i]) return false;
    return true;
}
bool all_distinct() {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a.size()!=n || b.size()!=n) return false;
    REP(i,1,n-1) if (a[i] == a[i-1]) return false;
    REP(i,1,n-1) if (b[i] == b[i-1]) return false;
    return true;
}
bool is_1n_permutation() {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    if (a.size()!=n || b.size()!=n) return false;
    REP(i,0,n-1) if (a[i] != i || b[i] != i) return false;
    return true;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);

    n = inf.readInt(MN_N[s], MX_N[s]);
    inf.readChar('\n');

    // a
    REP(i,1,n) {
        int x = inf.readInt(MN_AB, MX_AB);
        a.push_back(x);
        if (i==n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    // b
    REP(i,1,n) {
        int x = inf.readInt(MN_AB, MX_AB);
        b.push_back(x);
        if (i==n) inf.readChar('\n');
        else inf.readChar(' ');
    }
    inf.readEof();

    ensuref(same_permutation(), "a != b");
    ensuref(all_distinct(), "a, b should contain n distinct numbers");
    if (s==1) {
        ensuref(is_1n_permutation(), "a, b should be 0 ~ n-1 permutation");
    }
    return 0;
}
