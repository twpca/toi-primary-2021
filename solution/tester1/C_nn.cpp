#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
using u64 = std::uint64_t;
struct ele_t
{
    int x;
    int y;
    int i;
};
struct bit_t{
    int l;
    int i;
    int x;
    bool operator<(const bit_t &o)const{
        return std::tie(l, i, x) < std::tie(o.l, o.i, o.x);
    }
};
template <class T> bit_t qry(T &bit, int x)
{
    bit_t ans{0, 0x7FFFFFFF, 0x7FFFFFFF};
    for(int i=1;i<=x;++i)
        ans = std::max(ans, bit[i]);
    return ans;
}
template <class T> void mod(T &bit, int x, bit_t v)
{
    bit[x] = v;
}
bool solve(std::istream &is, std::ostream &os)
{
    int n;
    if (!(is >> n))
        return false;
    std::vector<ele_t> a(n);
    {
        std::map<int, int> mp;
        for (int i = 0; i < n; ++i)
        {
            int k{};
            if (!(is >> k))
                return false;
            mp[k] = i;
            a[i].i = k;
            a[i].x = i;
        }
        for (int i = 0; i < n; ++i)
        {
            int k{};
            if (!(is >> k))
                return false;
            a[mp[k]].y = n - i;
        }
    }
    std::vector<int> selections(n);
    std::vector<bit_t> bit(n + 1);
    std::for_each(a.rbegin(), a.rend(), [&bit, &selections](ele_t &e) {
        bit_t t = qry(bit, e.y);
        selections[e.x] = t.x;
        bit_t v{t.l + 1, e.i, e.x};
        mod(bit, e.y, v);
    });
    for (int i = qry(bit, n).x; i != 0x7FFFFFFF;)
    {
        os << a[i].i;
        i = selections[i];
        if (i == 0x7FFFFFFF)
            os << '\n';
        else
            os << ' ';
    }
    return true;
}
int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    while (solve(std::cin, std::cout))
        ;
}
