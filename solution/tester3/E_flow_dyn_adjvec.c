#include<limits.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
   int to, cap, w, rev;
}Arc;

typedef struct{
   Arc *data;
   int len, cap;
}VecArc;

VecArc VecArc_new(void){
   return (VecArc){.data=NULL, .len=0, .cap=0};
}

void VecArc_push(VecArc *this, Arc a){
   if(this->len == this->cap){
      this->cap = this->cap? 2*this->cap: 1;
      this->data = realloc(this->data, this->cap*sizeof*this->data);
   }
   this->data[this->len++] = a;
}

void VecArc_drop(VecArc *this){
   free(this->data);
}

typedef struct{
   int n, *h;
   VecArc *g;
}Flow;

Flow Flow_new(int n){
   int *h = malloc(n*sizeof*h);
   VecArc *g = malloc(n*sizeof*g);
   for(int i=0; i<n; ++i){
      g[i] = VecArc_new();
   }
   return (Flow){.n=n, .h=h, .g=g};
}

void Flow_insert_arc(Flow *this, int u, int v, int cap, int w){
   VecArc_push(this->g+u, (Arc){.to=v, .cap=cap, .w=w, .rev=this->g[v].len});
   VecArc_push(this->g+v, (Arc){.to=u, .cap=0, .w=-w, .rev=this->g[u].len-1});
}

void Flow_h_init(Flow *this){
   memset(this->h, 0, this->n*sizeof*this->h);
   int *bf = malloc((this->n+1)*sizeof*bf), b=0, e=this->n;
   bool *inq = malloc(this->n);
   for(int i=0; i<this->n; ++i){
      bf[i] = i;
   }
   memset(inq, true, this->n);
   while(e != b){
      int u = bf[b++];
      if(b > this->n){
         b = 0;
      }
      inq[u] = false;
      for(Arc *it=this->g[u].data; it!=this->g[u].data+this->g[u].len; ++it) if(it->cap){
         if(this->h[it->to] > this->h[u] + it->w){
            this->h[it->to] = this->h[u] + it->w;
            if(!inq[it->to]){
               bf[e++] = it->to;
               if(e > this->n){
                  e = 0;
               }
               inq[it->to] = true;
            }
         }
      }
   }
   free(inq);
   free(bf);
}

int Flow_mincost_maxflow(Flow *this, int s, int t){
   Flow_h_init(this);
   int *d = malloc(this->n*sizeof*d);
   bool *vis = malloc(this->n);
   int *pv = malloc(this->n*sizeof*pv);
   int *pe = malloc(this->n*sizeof*pe);
   int res = 0;
   while(1){
      for(int i=0; i<this->n; ++i){
         d[i] = INT_MAX;
      }
      d[s] = 0;
      memset(vis, false, this->n);
      for(int _=this->n; _-->0; ){
         int u = -1;
         for(int i=0; i<this->n; ++i) if(!vis[i]){
            if(u==-1 || d[u]>d[i]){
               u = i;
            }
         }
         if(d[u] == INT_MAX){
            break;
         }
         vis[u] = true;
         for(Arc *it=this->g[u].data; it!=this->g[u].data+this->g[u].len; ++it) if(it->cap){
            if(d[it->to] > d[u] + (it->w+this->h[u]-this->h[it->to])){
               d[it->to] = d[u] + (it->w+this->h[u]-this->h[it->to]);
               pv[it->to] = u;
               pe[it->to] = it-this->g[u].data;
            }
         }
      }
      if(d[t] == INT_MAX){
         break;
      }
      int df = INT_MAX;
      for(int u=t; u!=s; u=pv[u]){
         if(df > this->g[pv[u]].data[pe[u]].cap){
            df = this->g[pv[u]].data[pe[u]].cap;
         }
      }
      res += df*(d[t]-this->h[s]+this->h[t]);
      for(int u=t; u!=s; u=pv[u]){
         this->g[pv[u]].data[pe[u]].cap -= df;
         this->g[u].data[this->g[pv[u]].data[pe[u]].rev].cap += df;
      }
      for(int i=0; i<this->n; ++i) if(d[i] < INT_MAX){
         this->h[i] += d[i];
      }
   }
   free(pe);
   free(pv);
   free(vis);
   free(d);
   return res;
}

void Flow_drop(Flow *this){
   for(int i=this->n; i-->0; ){
      VecArc_drop(this->g+i);
   }
   free(this->g);
   free(this->h);
}

int main(void){
   int n; scanf("%d", &n);
   Flow f = Flow_new(2*n+2);
   for(int i=0; i<n; ++i){
      Flow_insert_arc(&f, 0, i+1, 1, 0);
      Flow_insert_arc(&f, n+i+1, 2*n+1, 1, 0);
   }
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      int w; scanf("%d", &w);
      Flow_insert_arc(&f, i+1, n+j+1, 1, -w);
   }
   printf("%d\n", -Flow_mincost_maxflow(&f, 0, 2*n+1));
   for(int i=0; i<n; ++i){
      printf("%d%c", f.h[i+1], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", -f.h[n+i+1], " \n"[i==n-1]);
   }
   Flow_drop(&f);
}
