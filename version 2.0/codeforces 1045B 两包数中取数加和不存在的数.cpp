/*
 * @Samaritan_infi
 */
/// 题意: 给出n(2e5), m(1e9), 然后 n 个数, n 个数相当于一个包，m中剩余的数作为另一个包
///         问从两个包中取数加和不能表示的数有哪些
/// 题解: 设 p 不能被表示, 即 p = ai + aj, 都在一个包中, 我们枚举结点 i
///       考虑到 (a + b) % m == p, 若 a < p 则 b < p, 若 a > p 则 b > p
///       即考虑a[0] + a[i] 不能被表示, 同时不能被a[1], a[2]... 表示,
///       所以前面的数和后面的数应当两两匹配, 和为 p, 即前后作差为回文串 O(n)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 2e6 + 5;
vector<int> manacher(vector<int> a) {
    int n = a.size(), m = (n << 1) - 1;
    vector<int> b(m, -1), p(m, 0);
    for (int i = 0; i < n; ++i) b[i << 1] = a[i];
    int x = 0;
    for (int i = 1; i < m; ++i) {
        if (i <= x + p[x]) p[i] = min(p[(x << 1) - i], x + p[x] - i);
        while (i - p[i] - 1 >= 0 && i + p[i] + 1 < m && b[i - p[i] - 1] == b[i + p[i] + 1])
            ++p[i];
        if (i + p[i] >= x + p[x]) x = i;
    }
    for (int i = 0; i < m; ++i)
        if (i - p[i] == 0 || i + p[i] == m - 1) ++p[i];
    for (int i = 0; i < m; ++i) p[i] >>= 1;
    return p;
}
void show (vector<int> p) { for (int i = 0; i < p.size(); i++) cout << p[i] << " "; cout << endl; }
int main () {
    int n, m; scanf("%d %d", &n, &m);
    vector<int> arr(n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    vector<int> brr(n);
    for (int i = 0; i < n - 1; i++) brr[i] = arr[i+1] - arr[i];
    brr[n-1] = (arr[0] + m - arr[n-1]) % m;
    vector<int> p = manacher(brr);
    auto palindrome = [&](int l, int r) {
        return l == r || p[l + r - 1] >= r - l >> 1;
    };
    vector<int> ans;
    for (int i = 0; i < n; i++) if (palindrome(0, i) && palindrome(i, n))
        ans.push_back((arr[0] + arr[i]) % m);
    printf("%d\n", ans.size());
    if (ans.size()) {
        sort (ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); i++)
            printf("%d ", ans[i]);
    }
    return 0;
}
