#include<algorithm>
#include<tuple>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;
using i64 = long long;

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<int> t(n), s(n), d(n);
   for(int i=1; i<=n-1; ++i){
      scanf("%d", &t[i]);
   }
   for(int i=0; i<n; ++i){
      scanf("%d", &s[i]);
   }
   for(int i=0; i<n; ++i){
      scanf("%d", &d[i]);
   }
   auto time_dust = [&s, &d, &m](int last, int x) -> pair<i64, i64>{
      i64 fi=0, se=0;
      for(int i=0; i<=last; ++i) if(s[i] >= x){
         i64 dfi = (s[i]-x)/d[i]+1;
         if((fi += dfi) > m){
            return {m+1, -1};
         }
         se += dfi*(2*s[i]-(dfi-1)*d[i])/2;
      }
      return {fi, se};
   };
   int x_min = 0, x_max = 0;
   i64 ans = 0;
   for(int i=0; i<n; ++i){
      if((m -= t[i]) <= 0) break;
      x_max = max(x_max, s[i]);
      if(d[i] == 0){
         x_min = max(x_min, s[i]);
      }
      int lb = x_min, ub = x_max+1;
      while(ub-lb > 1){
         int x = lb+(ub-lb)/2;
         (time_dust(i, x).first<=m? ub: lb) = x;
      }
      i64 time, dust;
      tie(time, dust) = time_dust(i, ub);
      ans = max(ans, dust+(m-time)*lb);
   }
   printf("%lld\n", ans);
}
