#include<algorithm>
#include<limits>
#include<vector>

template<typename T> struct Hungarian{
   Hungarian() = default;
   explicit Hungarian(int n): w(n*n), lx(n), ly(n), slack(n), mx(n), my(n), px(n), py(n), sy(n){}
   int size() const noexcept{
      return lx.size();
   }
   T &operator()(int x, int y) noexcept{
      return w[x*size()+y];
   }
   T run(){
      constexpr T INF = std::numeric_limits<T>::max();
      int const n = size();
      fill(ly.begin(), ly.end(), 0);
      fill(my.begin(), my.end(), -1);
      for(int x=0; x<n; ++x){
         lx[x] = *max_element(w.cbegin()+x*n, w.cbegin()+(x+1)*n);
      }
      for(int x=0; x<n; ++x){
         fill(slack.begin(), slack.end(), INF);
         fill(px.begin(), px.end(), -1);
         fill(py.begin(), py.end(), -1);
         px[x] = -2;
         if(dfs(x)){
            continue;
         }
         while(1){
            T d = INF;
            for(int y=0; y<n; ++y) if(py[y] == -1){
               d = std::min(d, slack[y]);
            }
            for(int x2=0; x2<n; ++x2) if(px[x2] != -1){
               lx[x2] -= d;
            }
            for(int y=0; y<n; ++y){
               if(py[y] != -1){
                  ly[y] += d;
               }else slack[y] -= d;
            }
            for(int y=0; y<n; ++y) if(py[y]==-1 && slack[y]==0){
               py[y] = sy[y];
               if(my[y] == -1){
                  augment(y);
                  goto next_x;
               }
               px[my[y]] = y;
               if(dfs(my[y])){
                  goto next_x;
               }
            }
         }
         next_x:;
      }
      T res = 0;
      for(int y=0; y<n; ++y){
         mx[my[y]] = y;
         res += w[my[y]*n+y];
      }
      return res;
   }
// private:
   std::vector<T> w, lx, ly, slack;
   std::vector<int> mx, my, px, py, sy;
   bool dfs(int x){
      int const n = size();
      for(int y=0; y<n; ++y) if(py[y] == -1){
         T d = lx[x]+ly[y]-w[x*n+y];
         if(d == 0){
            py[y] = x;
            if(my[y] == -1){
               augment(y);
               return true;
            }
            if(px[my[y]] == -1){
               px[my[y]] = y;
               if(dfs(my[y])){
                  return true;
               }
            }
         }else if(slack[y] > d){
            slack[y] = d; sy[y] = x;
         }
      }
      return false;
   }
   void augment(int y){
      while(y != -2){
         my[y] = py[y];
         y = px[my[y]];
      }
   }
};

#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   Hungarian<int> g(n);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      scanf("%d", &g(i, j));
   }
   printf("%d\n", g.run());
   for(int i=0; i<n; ++i){
      printf("%d%c", g.lx[i], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", g.ly[i], " \n"[i==n-1]);
   }
}
