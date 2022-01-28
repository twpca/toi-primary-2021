#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
struct ele_t
{
    int x;
    int y;
    int i;
};
struct stack_t
{
    int x;
    int y;
    int i;
};
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
            a[mp[k]].y = i;
        }
    }
    std::vector<std::vector<stack_t>> b;
    std::vector<int> selections(n);
    std::for_each(a.rbegin(), a.rend(), [&b, &selections](ele_t &e) {
        auto it = std::lower_bound(b.begin(), b.end(), e,
                                   [](std::vector<stack_t> &s, const ele_t &e) {
                                       return s.back().y > e.y;
                                   });
        if (it == b.end())
        {
            b.push_back(std::vector<stack_t>{});
            it = b.end() - 1;
        }
        {
            auto &c = *it;
            for (; !c.empty() && c.back().i < e.i; c.pop_back())
                ;
            c.push_back(stack_t{e.x, e.y, e.i});
        }
        if (it != b.begin())
        {
            auto &d = *(it - 1);
            auto kt = d.end() - 1;
            for (; kt >= d.begin() && kt->y >= e.y; --kt)
                ;
            assert(kt + 1 < d.end());
            selections[e.x] = (kt + 1)->x;
        }
        else
        {
            selections[e.x] = -1;
        }
    });
    for (int i = b.back().front().x; i != -1;)
    {
        os << a[i].i;
        i = selections[i];
        if (i == -1)
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
