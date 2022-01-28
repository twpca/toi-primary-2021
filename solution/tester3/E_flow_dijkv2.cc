#include<algorithm>
#include<limits>
#include<queue>
#include<vector>

template<typename CapT, typename CostT>
struct MinCostFlow{
   struct arc{
      int to, rev;
      CapT cap, flow;
      CostT cost;
      arc() = default;
      constexpr arc(int v, int j, CapT c, CostT w) noexcept: to(v), rev(j), cap(c), flow(0), cost(w){}
   };
   MinCostFlow() = default;
   explicit MinCostFlow(int n): g(n){}
   void insert_arc(int u, int v, CapT c, CostT w){
      g[u].emplace_back(v, g[v].size(), c, w);
      g[v].emplace_back(u, g[u].size()-1, 0, -w);
   }
   CostT min_cost(int s, int t, CapT f = std::numeric_limits<CapT>::max()){
      constexpr CostT INF = std::numeric_limits<CostT>::max();
      CostT res = 0;
      while(f){
         if(h.empty()){
            h_init();
         }
         std::vector<CostT> d(g.size(), INF);
         std::vector<int> pv(g.size()), pa(g.size());
         std::vector<bool> vis(g.size());
         d[s] = 0;
         for(int i=0; i<(int)g.size(); ++i){
            int u = -1;
            for(int j=0; j<(int)g.size(); ++j) if(!vis[j]){
               if(u==-1 || d[u]>d[j]){
                  u = j;
               }
            }
            vis[u] = true;
            if(d[u] == INF) break;
            if(u == t) continue;
            for(int j=0; j<(int)g[u].size(); ++j){
               auto &a = g[u][j];
               if(a.flow == a.cap) continue;
               if(d[a.to] > d[u]+a.cost+h[u]-h[a.to]){
                  d[a.to] = d[u]+a.cost+h[u]-h[a.to];
                  pv[a.to] = u; pa[a.to] = j;
               }
            }
         }
         if(d[t] == INF){
            break;
         }
         CapT df = f;
         for(int u=t; u!=s; u=pv[u]){
            auto &a = g[pv[u]][pa[u]];
            df = std::min(df, a.cap-a.flow);
         }
         for(int u=t; u!=s; u=pv[u]){
            auto &a = g[pv[u]][pa[u]];
            a.flow += df;
            g[u][a.rev].flow -= df;
         }
         f -= df;
         res += df*(d[t]+h[t]-h[s]);
         for(int u=0; u<(int)g.size(); ++u) if(d[u] < INF){
            h[u] += d[u];
         }
      }
      return res;
   }
// private:
   std::vector<std::vector<arc>> g;
   std::vector<CostT> h;
   void h_init(){
      h.resize(g.size(), 0);
      std::queue<int> bf;
      for(int i=0; i<(int)g.size(); ++i){
         bf.push(i);
      }
      std::vector<bool> inq(g.size(), true);
      while(!bf.empty()){
         int u = bf.front(); bf.pop();
         inq[u] = false;
         for(auto &a: g[u]) if(a.flow<a.cap && h[a.to]>h[u]+a.cost){
            h[a.to] = h[u] + a.cost;
            if(!inq[a.to]){
               bf.push(a.to);
               inq[a.to] = true;
            }
         }
      }
   }
};

#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   MinCostFlow<int, int> mcf(2*n+2);
   for(int i=1; i<=n; ++i){
      mcf.insert_arc(0, i, 1, 0);
   }
   for(int i=n+1; i<=2*n; ++i){
      mcf.insert_arc(i, 2*n+1, 1, 0);
   }
   for(int i=1; i<=n; ++i) for(int j=n+1; j<=2*n; ++j){
      int aij; scanf("%d", &aij);
      mcf.insert_arc(i, j, 1, -aij);
   }
   printf("%d\n", -mcf.min_cost(0, 2*n+1));
   for(int i=0; i<n; ++i){
      printf("%d%c", mcf.h[i+1], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", -mcf.h[n+i+1], " \n"[i==n-1]);
   }
}
