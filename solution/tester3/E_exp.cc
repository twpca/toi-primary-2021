#include<algorithm>
#include<tuple>
#include<vector>
#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   vector<int> a(n);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      int aij; scanf("%d", &aij);
      a[i] |= aij<<j;
   }
   auto ans = make_tuple(n+1, 0, 0);
   for(int r=0; r<1<<n; ++r){
      int m = 0, c = 0;
      for(int i=0; i<n; ++i){
         if(r>>i&1){
            ++m;
         }else c |= a[i];
      }
      for(int i=0; i<n; ++i){
         m += c>>i&1;
      }
      ans = min(ans, {m, r, c});
   }
   printf("%d\n", get<0>(ans));
   for(int i=0; i<n; ++i){
      printf("%d%c", get<1>(ans)>>i&1, " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", get<2>(ans)>>i&1, " \n"[i==n-1]);
   }
}
