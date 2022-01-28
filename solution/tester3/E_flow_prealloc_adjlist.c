#include<limits.h>
#include<stdbool.h>
#include<stdio.h>
#include<string.h>

#define N 500
#define V (2*N+2)
#define E (2*N*N+4*N)
int n, m, head[V], next[E+1], bf[V+1], h[V], d[V], pv[V], pe[V];
struct Arc{
   int to, cap, w, rev;
}g[E+1];
bool inq[V], vis[V];

void insert_arc(int u, int v, int cap, int w){
   next[++m] = head[u]; head[u] = m;
   g[m] = (struct Arc){.to=v, .cap=cap, .w=w, .rev=m+1};
   next[++m] = head[v]; head[v] = m;
   g[m] = (struct Arc){.to=u, .cap=0, .w=-w, .rev=m-1};
}

int main(void){
   scanf("%d", &n);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      int w; scanf("%d", &w);
      insert_arc(i+1, n+j+1, 1, -w);
   }
   for(int i=0; i<n; ++i){
      insert_arc(0, i+1, 1, 0);
      insert_arc(n+i+1, 2*n+1, 1, 0);
   }
   for(int i=0; i<2*n+2; ++i){
      bf[i] = i; inq[i] = true;
   }
   int b = 0, e = n;
   while(b != e){
      int u = bf[b++];
      if(b == n+1) b = 0;
      inq[u] = false;
      for(int i=head[u]; i; i=next[i]){
         if(g[i].cap && h[g[i].to]>h[u]+g[i].w){
            h[g[i].to] = h[u]+g[i].w;
            if(!inq[g[i].to]){
               bf[e++] = g[i].to;
               if(e == n+1) e = 0;
               inq[g[i].to] = true;
            }
         }
      }
   }
   int const s = 0, t = 2*n+1;
   int min_cost = 0;
   while(1){
      for(int i=0; i<2*n+2; ++i){
         d[i] = INT_MAX;
      }
      memset(vis, false, 2*n+2);
      d[s] = 0;
      for(int _=2*n+2; _-->0; ){
         int u = -1;
         for(int i=0; i<2*n+2; ++i) if(!vis[i] && (u==-1 || d[u]>d[i])){
            u = i;
         }
         if(d[u] == INT_MAX) break;
         vis[u] = true;
         for(int i=head[u]; i; i=next[i]) if(g[i].cap && d[g[i].to]>d[u]+g[i].w+h[u]-h[g[i].to]){
            d[g[i].to] = d[u]+g[i].w+h[u]-h[g[i].to];
            pv[g[i].to] = u; pe[g[i].to] = i;
         }
      }
      if(d[t] == INT_MAX) break;
      int df = INT_MAX;
      for(int u=t; u!=s; u=pv[u]){
         if(df > g[pe[u]].cap) df = g[pe[u]].cap;
      }
      min_cost += df*(d[t]-h[s]+h[t]);
      for(int u=t; u!=s; u=pv[u]){
         g[pe[u]].cap -= df;
         g[g[pe[u]].rev].cap += df;
      }
      for(int i=0; i<2*n+2; ++i) if(d[i] != INT_MAX){
         h[i] += d[i];
      }
   }
   printf("%d\n", -min_cost);
   for(int i=0; i<n; ++i){
      printf("%d%c", h[i+1], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", -h[n+i+1], " \n"[i==n-1]);
   }
}
