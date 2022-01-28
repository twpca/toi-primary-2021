// O(2^n * n)
#include<bits/stdc++.h>
#define REP(x,y,z) for(int x=y;x<=z;x++)
#define MSET(x,y) memset(x,y,sizeof(x))
#define B(x) (1<<(x))
#define M 25
using namespace std;
int n,in[M],num[M];
vector<int> ans;
int main()
{
    while (~scanf("%d", &n)) {
        ans.clear();
        unordered_map<int,int> mp;
        REP(i,1,n) {
            int x;
            scanf("%d", &x);
            mp[x] = i;
        }
        REP(i,1,n) {
            scanf("%d", &num[i]);
            in[i] = mp[num[i]];
        }

        int msk = B(n) - 1;
        REP(i,0,msk) {
            vector<int> tmp;
            REP(j,1,n) if (B(j-1) & i) tmp.push_back(j);

            auto check = [&]() {
                // increase
                int sz = tmp.size();
                REP(j,1,sz-1) if (in[tmp[j]] <= in[tmp[j-1]]) return false;
                // size
                if (tmp.size() != ans.size()) {
                    return tmp.size() > ans.size();
                }
                // lex
                REP(j,0,sz-1) if (ans[j] != tmp[j]) return num[tmp[j]] > num[ans[j]];
                return false;
            };
            if (check()) {
                ans = tmp;
            }
        }

        REP(i,0,(int)ans.size()-1) {
            printf("%d%c", num[ans[i]], i==(int)ans.size()-1 ? '\n' : ' ');
        }
    }
    return 0;
}
