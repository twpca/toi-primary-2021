#include<algorithm>
#include<limits>
#include<queue>
#include<utility>
#include<vector>

template<typename CapT, typename CostT>
struct CostFlowArc{
   int to, rev;
   CapT cap, flow;
   CostT w;
   CostFlowArc() = default;
   constexpr CostFlowArc(int v, int i, CapT c, CostT w) noexcept: to(v), rev(i), cap(c), flow(0), w(w){}
};

template<typename ArcT>
struct ArcEnabledT{
   bool operator()(ArcT const&){
      return true;
   }
};

template<typename CapT, typename CostT>
struct ArcEnabledT<CostFlowArc<CapT, CostT>>{
   bool operator()(CostFlowArc<CapT, CostT> const &a){
      return a.flow < a.cap;
   }
};

template<typename ArcT>
bool arc_enabled(ArcT const &a){
   return ArcEnabledT<ArcT>()(a);
}

template<typename ArcT>
std::vector<decltype(std::declval<ArcT>().w)> bellman_ford(int n, std::vector<ArcT> const *g, int s, int *pv = nullptr, int *pa = nullptr){
   using WeightT = decltype(std::declval<ArcT>().w);
   std::vector<WeightT> d(n, std::numeric_limits<WeightT>::max());
   std::queue<int> q;
   std::vector<bool> inq(n);
   d[s] = 0; q.push(s); inq[s] = true;
   while(!q.empty()){
      int u = q.front();
      q.pop(); inq[u] = false;
      for(int i=0; i<(int)g[u].size(); ++i){
         auto &a = g[u][i];
         if(arc_enabled(a) && d[a.to] > d[u]+a.w){
            d[a.to] = d[u]+a.w;
            if(pv) pv[a.to] = u;
            if(pa) pa[a.to] = i;
            if(!inq[a.to]){
               q.push(a.to); inq[a.to] = true;
            }
         }
      }
   }
   return d;
}

template<typename CapT, typename CostT>
struct MinCostFlow{
   using Arc = CostFlowArc<CapT, CostT>;
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
         std::vector<int> pv(g.size()), pa(g.size());
         auto d = bellman_ford(g.size(), g.data(), s, pv.data(), pa.data());
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
         res += df*d[t];
      }
      return res;
   }
// private:
   std::vector<std::vector<Arc>> g;
};

#include<cstdio>
using namespace std;

struct Arc{
   int to, w;
   Arc() = default;
   constexpr Arc(int to, int w) noexcept: to(to), w(w){}
};

int main(){
   int n; scanf("%d", &n);
   vector<vector<int>> a(n, vector<int>(n));
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      scanf("%d", &a[i][j]);
   }
   MinCostFlow<int, int> mcf(2*n+2);
   for(int i=0; i<n; ++i){
      mcf.insert_arc(0, i+1, 1, 0);
      mcf.insert_arc(n+i+1, 2*n+1, 1, 0);
   }
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      mcf.insert_arc(i+1, n+j+1, 1, -a[i][j]);
   }
   printf("%d\n", -mcf.min_cost(0, 2*n+1));
   vector<int> match(n);
   for(int i=0; i<n; ++i){
      for(auto &a: mcf.g[i+1]) if(a.flow == 1){
         match[i] = a.to-n-1;
         break;
      }
   }
   vector<vector<Arc>> g(n);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) if(i != j){
      g[i].emplace_back(j, a[j][match[j]]-a[i][match[j]]);
   }
   auto r = bellman_ford(n, g.data(), 0);
   int min_r = *min_element(r.cbegin(), r.cend());
   vector<int> c(n);
   for(int i=0; i<n; ++i){
      r[i] -= min_r;
      c[match[i]] = a[i][match[i]] - r[i];
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", r[i], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", c[i], " \n"[i==n-1]);
   }
}
