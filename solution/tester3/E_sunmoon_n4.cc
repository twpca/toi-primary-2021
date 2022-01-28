#include<bits/stdc++.h>
using namespace std;

#define MAXN 500
#define INF INT_MAX
int n;
int g[MAXN][MAXN],lx[MAXN],ly[MAXN],slack_y[MAXN];
int match_y[MAXN];
bool vx[MAXN],vy[MAXN];
bool dfs(int x){
   if(vx[x])return 0;
   vx[x]=1;
   for(int y=0,t;y<n;++y){
      if(vy[y])continue;
      t=lx[x]+ly[y]-g[x][y];
      if(t==0){
         vy[y]=1;
         if(match_y[y]==-1||dfs(match_y[y])){
            match_y[y]=x;
            return 1;
         }
      }else if(slack_y[y]>t)slack_y[y]=t;
   }
   return 0;
}
inline int km(){
   memset(ly,0,sizeof(int)*n);
   memset(match_y,-1,sizeof(int)*n);
   for(int x=0;x<n;++x){
      lx[x]=-INF;
      for(int y=0;y<n;++y){
         lx[x]=max(lx[x],g[x][y]);
      }
   }
   for(int x=0;x<n;++x){
      for(int y=0;y<n;++y)slack_y[y]=INF;
      for(;;){
         memset(vx,0,sizeof(bool)*n);
         memset(vy,0,sizeof(bool)*n);
         if(dfs(x))break;
         int cut=INF;
         for(int y=0;y<n;++y){
            if(!vy[y]&&cut>slack_y[y])cut=slack_y[y];
         }
         for(int j=0;j<n;++j){
            if(vx[j])lx[j]-=cut;
            if(vy[j])ly[j]+=cut;
            else slack_y[j]-=cut;
         }
      }
   }
   int ans=0;
   for(int y=0;y<n;++y)if(g[match_y[y]][y]!=-INF)ans+=g[match_y[y]][y];
   return ans;
}

int main(){
   scanf("%d", &n);
   for(int i=0; i<n; ++i) for(int j=0; j<n; ++j){
      scanf("%d", g[i]+j);
   }
   printf("%d\n", km());
   for(int i=0; i<n; ++i){
      printf("%d%c", lx[i], " \n"[i==n-1]);
   }
   for(int i=0; i<n; ++i){
      printf("%d%c", ly[i], " \n"[i==n-1]);
   }
}
