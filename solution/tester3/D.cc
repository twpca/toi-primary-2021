#include<array>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

constexpr int lg2(int n) noexcept{
   int res = 0;
   if(n >= 65536) n>>=16, res|=16;
   if(n >= 256) n>>=8, res|=8;
   if(n >= 16) n>>=4, res|=4;
   if(n >= 4) n>>=2, res|=2;
   if(n >= 2) res|=1;
   return res;
}

struct Arc{
   int to, w, a, b, p;
   Arc() = default;
   constexpr Arc(int to, int w, int a, int b, int p) noexcept: to(to), w(w), a(a), b(b), p(p){}
};

struct Solver{
   Solver() = default;
   explicit Solver(int n): lgn(lg2(n-1)), g(n), d(n), pv((lgn+1)*n), pa(n), nobori((lgn+1)*n), kudari((lgn+1)*n){}
   void insert_edge(int u, int v, int w, int a, int b, int p){
      g[u].emplace_back(v, w, a, b, p);
      g[v].emplace_back(u, w, b, a, p);
   }
   void preprocess(){
      dfs(0, 0, 0);
      int n = g.size();
      for(int i=1; i<=lgn; ++i){
         for(int u=0; u<n; ++u) if(d[u] >= 1<<i){
            pv[id(i, u)] = pv[id(i-1, pv[id(i-1, u)])];
         }
      }
      for(int u=1; u<n; ++u){
         int w, a, b, p;
         w = g[u][pa[u]].w;
         a = g[u][pa[u]].a;
         b = g[u][pa[u]].b;
         p = g[u][pa[u]].p;
         for(int m=0; m<60; ++m){
            nobori[u][m] = (a-m+60)%p+w;
            kudari[u][m] = (b-m+60)%p+w;
         }
      }
      for(int i=1; i<=lgn; ++i){
         for(int u=0; u<n; ++u) if(d[u] >= 1<<i){
            int v = pv[id(i-1, u)];
            for(int m=0; m<60; ++m){
               int a = nobori[id(i-1, u)][m], b = kudari[id(i-1, v)][m];
               nobori[id(i, u)][m] = a+1+nobori[id(i-1, v)][(m+a+1)%60];
               kudari[id(i, u)][m] = b+1+kudari[id(i-1, u)][(m+b+1)%60];
            }
         }
      }
   }
   int query(int m, int s, int t) const{
      int a = lca(s, t), res = -1;
      for(int i=lgn; i>=0; --i) if(d[s]-d[a] >= 1<<i){
         res += 1+nobori[id(i, s)][(m+res+1)%60];
         s = pv[id(i, s)];
      }
      vector<int> pt{t};
      for(int i=lgn; i>=0; --i) if(d[t]-d[a] >= 1<<i){
         t = pv[id(i, t)];
         pt.push_back(t);
      }
      for(int i=0, j=pt.size()-1; j>0; ++i){
         if(d[pt[j-1]]-d[pt[j]] == 1<<i){
            res += 1+kudari[id(i, pt[--j])][(m+res+1)%60];
         }
      }
      return res;
   }
private:
   int lgn;
   vector<vector<Arc>> g;
   vector<int> d, pv, pa;
   vector<array<int, 60>> nobori, kudari;
   int id(int i, int u) const noexcept{
      return i*g.size()+u;
   }
   void dfs(int u, int p, int dep){
      d[u] = dep;
      pv[u] = p;
      for(int i=0; i<(int)g[u].size(); ++i){
         auto &a = g[u][i];
         if(a.to == p){
            pa[u] = i; continue;
         }
         dfs(a.to, u, dep+1);
      }
   }
   int lca(int u, int v) const noexcept{
      if(d[u] < d[v]) swap(u, v);
      for(int i=lgn; i>=0; --i) if(d[u]-d[v] >= 1<<i){
         u = pv[id(i, u)];
      }
      if(u == v) return u;
      for(int i=lgn; i>=0; --i) if(d[u]>=1<<i && pv[id(i, u)]!=pv[id(i, v)]){
         u = pv[id(i, u)];
         v = pv[id(i, v)];
      }
      return pv[u];
   }
};

int main(){
   int n, q;
   scanf("%d%d", &n, &q);
   Solver solver(n);
   for(int i=1; i<=n-1; ++i){
      int u, v, w, a, b, p;
      scanf("%d%d%d%d%d%d", &u, &v, &w, &a, &b, &p);
      solver.insert_edge(u-1, v-1, w, a, b, p);
   }
   solver.preprocess();
   while(q-- > 0){
      int m, s, t;
      scanf("%*d%d%d%d", &m, &s, &t);
      printf("%d\n", solver.query(m, s-1, t-1));
   }
}
