#include<numeric>
#include<utility>
#include<vector>
#include<cstdio>
using namespace std;

struct Arc{
   int to, w;
   Arc() = default;
   constexpr Arc(int to, int w) noexcept: to(to), w(w){}
};

struct Solver{
   Solver() = default;
   Solver(int n, vector<Arc> const *g): first(n), dist(n), lg(2*n), st{vector<int>(2*n-1)}{
      vis.reserve(2*n-1);
      dep.reserve(2*n-1);
      dfs(g);
      iota(st[0].begin(), st[0].end(), 0);
      for(int i=2; i<=2*n-1; ++i){
         lg[i] = lg[i/2]+1;
      }
      for(int i=1; i<=lg[2*n-1]; ++i){
         st.emplace_back(2*n-(1<<i));
         for(int j=0; j<2*n-(1<<i); ++j){
            int i1 = st[i-1][j], i2 = st[i-1][j+(1<<i-1)];
            st[i][j] = dep[i2]<dep[i1]? i2: i1;
         }
      }
   }
   int query(int u, int v) const noexcept{
      return dist[u] + dist[v] - 2*dist[lca(u, v)];
   }
private:
   vector<int> vis, dep, first, dist, lg;
   vector<vector<int>> st;
   void dfs(vector<Arc> const *g, int u=0, int p=-1, int d1=0, int d2=0){
      first[u] = vis.size();
      dist[u] = d2;
      vis.push_back(u);
      dep.push_back(d1);
      for(size_t i=0; i<g[u].size(); ++i){
         int v = g[u][i].to, w = g[u][i].w;
         if(v != p){
            dfs(g, v, u, d1+1, d2+w);
            vis.push_back(u);
            dep.push_back(d1);
         }
      }
   }
   int lca(int u, int v) const noexcept{
      int l = first[u], r = first[v];
      if(l > r) swap(l, r);
      int k = lg[r-l+1], i1 = st[k][l], i2 = st[k][r-(1<<k)+1];
      return dep[i2]<dep[i1]? vis[i2]: vis[i1];
   }
};

int main(){
   int n, m;
   scanf("%d%d", &n, &m);
   vector<vector<Arc>> g(n);
   for(int i=1; i<=n-1; ++i){
      int u, v, w;
      scanf("%d%d%d%*d%*d%*d", &u, &v, &w);
      --u; --v;
      g[u].emplace_back(v, w+1);
      g[v].emplace_back(u, w+1);
   }
   Solver solver(n, g.data());
   while(m-- > 0){
      int s, t;
      scanf("%*d%*d%d%d", &s, &t);
      printf("%d\n", solver.query(s-1, t-1)-1);
   }
}
