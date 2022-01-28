#include<algorithm>
#include<functional>
#include<unordered_map>
#include<vector>
#include<climits>
#include<cstdio>
using namespace std;

int main(){
   int n; scanf("%d", &n);
   vector<int> x(n);
   unordered_map<int, int> risan(n);
   for(int i=0; i<n; ++i){
      scanf("%d", &x[i]);
      risan[x[i]] = i;
   }
   vector<int> a(n);
   for(int i=0; i<n; ++i){
      int yi; scanf("%d", &yi);
      a[i] = risan[yi];
   }
   vector<int> ext(n), dp{INT_MAX};
   for(int i=n-1; i>=0; --i){
      if(a[i] <= dp.back()){
         ext[i] = dp.size();
         dp.push_back(a[i]);
      }else{
         ext[i] = upper_bound(dp.cbegin(), dp.cend(), a[i], greater<>()) - dp.cbegin();
         dp[ext[i]] = a[i];
      }
   }
   int len = dp.size()-1;
   vector<int> ans;
   ans.reserve(len);
   for(int i=0; i<n; ++i){
      if(ext[i] == len){
         if(ans.empty() || x[ans[0]]<x[a[i]]){
            ans.clear(); ans.push_back(a[i]);
         }
      }else if(len-ext[i] < (int)ans.size()){
         if(ans[len-ext[i]-1]<=a[i] && x[ans[len-ext[i]]]<x[a[i]]){
            ans[len-ext[i]] = a[i]; ans.resize(len-ext[i]+1);
         }
      }else if(len-ext[i] == (int)ans.size()){
         if(ans[len-ext[i]-1] <= a[i]){
            ans.push_back(a[i]);
         }
      }
   }
   for(size_t i=0; i<ans.size(); ++i){
      printf("%d%c", x[ans[i]], " \n"[i+1==ans.size()]);
   }
}
