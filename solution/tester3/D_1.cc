#include<vector>
#include<cstdio>
using namespace std;

struct Arc{
   int to, w, a, p;
   Arc() = default;
   constexpr Arc(int to, int w, int a, int p) noexcept: to(to), w(w), a(a), p(p){}
};

int dfs(vector<Arc> const *g, int t, int m, int u, int pu){
   if(u == t){
      return m;
   }
   for(size_t i=0; i<g[u].size(); ++i){
      int v, w, a, p;
      v = g[u][i].to;
      w = g[u][i].w;
      a = g[u][i].a;
      p = g[u][i].p;
      if(v != pu){
         int res = dfs(g, t, m+(a-m%p+p)%p+w+1, v, u);
         if(res >= 0){
            return res;
         }
      }
   }
   return -1;
}

int main(){
   int n, q; scanf("%d%d", &n, &q);
   vector<vector<Arc>> g(n+1);
   for(int i=1; i<=n-1; ++i){
      int u, v, w, a, b, p;
      scanf("%d%d%d%d%d%d", &u, &v, &w, &a, &b, &p);
      g[u].emplace_back(v, w, a, p);
      g[v].emplace_back(u, w, b, p);
   }
   while(q-- > 0){
      int m, s, t;
      scanf("%*d%d%d%d", &m, &s, &t);
      printf("%d\n", dfs(g.data(), t, m, s, 0)-m-1);
   }
}
