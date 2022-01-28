#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <tuple>
#include <vector>
struct ele_t
{
    int y;
    int i;
};
struct stack_t
{
    int y;
    int i;
};
template <class JT, class IT>
std::pair<IT, int> max_index(JT b_st, IT a_st, IT a_ed)
{
    auto b_ed = b_st;
    IT max_i = a_ed;
    for (; a_st < a_ed; ++a_st)
    {
        const ele_t &e = *a_st;
        auto it = std::lower_bound(
            b_st, b_ed, e,
            [](const stack_t &s, const ele_t &e) { return s.y > e.y; });
        *it = stack_t{e.y, e.i};
        if (it == b_ed)
        {
            ++b_ed;
            max_i = a_st;
        }
        else if (it == b_ed - 1)
        {
            if (max_i->i < e.i)
            {
                max_i = a_st;
            }
        }
    };
    return {max_i, b_ed - b_st};
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
        }
        for (int i = 0; i < n; ++i)
        {
            int k{};
            if (!(is >> k))
                return false;
            a[mp[k]].y = i;
        }
    }
    std::reverse(a.begin(), a.end());
    std::vector<stack_t> b(n);

    auto start = a.end();
    int length = 0;
    {
        auto result = max_index(b.begin(), a.begin(), a.end());
        start = result.first;
        length = result.second;
        std::cout << start->i << (1 == length ? '\n' : ' ');
    }
    for (int i = length - 1; i > 0; --i)
    {
        a.erase(std::remove_if(
                    a.begin(), start,
                    [&start](const ele_t &e) { return e.y <= start->y; }),
                a.end());
        auto result = max_index(b.begin(), a.begin(), a.end());
        start = result.first;
        length = result.second;
        std::cout << start->i << (1 == length ? '\n' : ' ');
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
