#include<algorithm>
#include<array>
#include<vector>
#include<cstdio>
using namespace std;

struct SegTree{
   SegTree() = default;
   SegTree(int n, int *w, int *a, int *p): nodes(4*n){
      build(w, a, p, 1, 0, n-1);
   }
   int size() const noexcept{
      return nodes.size()>>2;
   }
   int query(int m, int l, int r) const noexcept{
      int m0 = m;
      m_query(m, l, r, 1, 0, size()-1);
      return m-m0-1;
   }
private:
   vector<array<int, 60>> nodes;
   void build(int *w, int *a, int *p, int i, int l, int r){
      if(l == r){
         for(int j=0; j<60; ++j){
            nodes[i][j] = (a[l]-j+60)%p[l]+w[l]+1;
         }
         return;
      }
      int m = l+(r-l)/2;
      build(w, a, p, 2*i, l, m);
      build(w, a, p, 2*i+1, m+1, r);
      for(int j=0; j<60; ++j){
         int lt = nodes[2*i][j];
         nodes[i][j] = lt+nodes[2*i+1][(j+lt)%60];
      }
   }
   void m_query(int &m, int ql, int qr, int i, int l, int r) const noexcept{
      if(r<ql || qr<l){
         return;
      }
      if(ql<=l && r<=qr){
         m += nodes[i][m%60];
         return;
      }
      int mid = l+(r-l)/2;
      m_query(m, ql, qr, 2*i, l, mid);
      m_query(m, ql, qr, 2*i+1, mid+1, r);
   }
};

int main(){
   int n, q; scanf("%d%d", &n, &q);
   vector<int> w(n-1), a(n-1), b(n-1), p(n-1);
   for(int i=0; i<n-1; ++i){
      scanf("%*d%*d%d%d%d%d", &w[i], &a[i], &b[n-i-2], &p[i]);
   }
   SegTree nobori(n-1, w.data(), a.data(), p.data());
   reverse(w.begin(), w.end());
   reverse(p.begin(), p.end());
   SegTree kudari(n-1, w.data(), b.data(), p.data());
   while(q-- > 0){
      int m, s, t;
      scanf("%*d%d%d%d", &m, &s, &t);
      printf("%d\n", s<t? nobori.query(m, s-1, t-2): kudari.query(m, n-s, n-t-1));
   }
}
