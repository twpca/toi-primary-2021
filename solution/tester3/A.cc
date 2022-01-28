#include<algorithm>
#include<array>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int N = 1024;
struct BitcntT{
   constexpr BitcntT() noexcept: a{}{
      for(int i=1; i<=N; ++i){
         a[i] = a[i>>1] + (i&1);
      }
   }
   constexpr signed char operator[](int i) const noexcept{
      return a[i];
   }
private:
   signed char a[N+1];
};
constexpr BitcntT bitcnt;

int main(){
   int n; scanf("%d", &n);
   vector<int> a(n);
   for(int i=0; i<n; ++i){
      scanf("%d", &a[i]);
   }
   stable_sort(a.begin(), a.end(), [](int x, int y){
      return bitcnt[x] < bitcnt[y];
   });
   for(int i=0; i<n; ++i){
      printf("%d%c", a[i], " \n"[i==n-1]);
   }
}
