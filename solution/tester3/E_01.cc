#include<algorithm>
#include<tuple>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

struct Solver{
   Solver() = default;
   explicit Solver(int n): a(n*n), mx(n), my(n), vis(n){}
   int size() const noexcept{
      return mx.size();
   }
   int &operator()(int i, int j) noexcept{
      return a[i*size()+j];
   }
   tuple<int, vector<bool>, vector<bool>> run(){
      int const n = size();
      fill(mx.begin(), mx.end(), -1);
      fill(my.begin(), my.end(), -1);
      int m = 0;
      for(int i=0; i<n; ++i){
         for(int j=0; j<n; ++j) if(a[i*n+j] && my[j]==-1){
            mx[i] = j; my[j] = i; ++m;
            break;
         }
      }
      for(int i=0; i<n; ++i) if(mx[i] == -1){
         for(int j=0; j<n; ++j){
            vis[j] = false;
         }
         m += dfs(i);
      }
      for(int i=0; i<n; ++i){
         vis[i] = false;
      }
      for(int i=0; i<n; ++i) if(mx[i] == -1){
         dfs(i);
      }
      vector<bool> r(n), c(n);
      for(int i=0; i<n; ++i){
         if(!vis[i]){
            r[i] = true;
         }else{
            for(int j=0; j<n; ++j) if(a[i*n+j]){
               c[j] = true;
            }
         }
      }
      return {m, move(r), move(c)};
   }
private:
   vector<int> a, mx, my;
   vector<bool> vis;
   bool dfs(int i){
      int const n = size();
      vis[i] = true;
      for(int j=0; j<n; ++j) if(a[i*n+j]){
         if(my[j]==-1 || !vis[my[j]] && dfs(my[j])){
            mx[i] = j; my[j] = i;
            return true;
         }
      }
      return false;
   }
};

int main(){
   int n; scanf("%d", &n);
   Solver solver(n);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      scanf("%d", &solver(i, j));
   }
   int m;
   vector<bool> r, c;
   tie(m, r, c) = solver.run();
   printf("%d\n", m);
   for(int i=0; i<n; ++i){
      printf("%d%c", (bool)r[i], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", (bool)c[i], " \n"[i==n-1]);
   }
}
