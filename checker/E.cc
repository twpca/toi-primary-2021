#define CMS
#define TESTSYS
#include"testlib.h"
#include<numeric>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int C = 2'000'000;

int main(int argc, char **argv){
   registerTestlibCmd(argc, argv);
   int n = inf.readInt();
   vector<vector<int>> a(n, vector<int>(n));
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      a[i][j] = inf.readInt();
   }
   ouf.strict = true;
   int m = ouf.readInt();
   if(m != ans.readInt()){
      quitf(_wa, "bad minimum");
   }
   ouf.readEoln();
   vector<int> r(n), c(n);
   for(int i=0; i<n; ++i){
      if(i > 0){
         ouf.readChar(' ');
      }
      r[i] = ouf.readInt(0, C);
   }
   ouf.readEoln();
   for(int i=0; i<n; ++i){
      if(i > 0){
         ouf.readChar(' ');
      }
      c[i] = ouf.readInt(0, C);
   }
   if(accumulate(r.cbegin(), r.cend(), 0) + accumulate(c.cbegin(), c.cend(), 0) != m){
      fprintf(stdout, "0.4\n");
      quitf(_pc(80), "good minimum, bad cover");
   }
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      if(a[i][j] > r[i]+c[j]){
         fprintf(stdout, "0.4\n");
         quitf(_pc(80), "good minimum, bad cover");
      }
   }
   quitf(_ok, "good");
}
