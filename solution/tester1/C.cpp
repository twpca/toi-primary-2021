#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include <map>
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
            auto kt = std::lower_bound(
                d.begin(), d.end(), e,
                [](stack_t &s, const ele_t &e) { return s.y < e.y; });
            assert(kt != d.end());
            selections[e.x] = kt->x;
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
    while (solve(std::cin, std::cout))
        ;
}
