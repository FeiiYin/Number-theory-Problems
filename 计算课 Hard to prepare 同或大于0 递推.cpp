/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

/// sum(0, n - 1) (C(n, i)*2^(k*(n-i))*(-1)^i) ^乘方  抑或为0？
/// 同或不为0时，分奇偶讨论，偶数时多2^k种方案

/// 递推计算
const int mod = 1e9 + 7;
ll quick_pow(ll a, ll b) {
    ll ans = 1;
    for (ll base = a; b; b >>= 1, base = (base * base) % mod)
        if (b & 1) ans = (ans * base) % mod;
    return ans;
}

const int N = 1e6 + 5;
ll pow_2[N];

ll solve (int n, int m) {
    if (n == 2) return pow_2[m] * (pow_2[m] - 1) % mod;
    if (n == 1) return pow_2[m];
    return ((pow_2[m] * quick_pow(pow_2[m] - 1, n - 2) % mod * (pow_2[m] + mod - 2) % mod) % mod + solve(n - 2, m)) % mod;
}

int main () {
    pow_2[0] = 1;
    for (int i = 1; i < N; i ++) pow_2[i] = (pow_2[i - 1] * 2) % mod;
    int _; scanf("%d", &_);
    while (_ --) {
        int n, m; scanf("%d %d", &n, &m);
        printf("%lld\n", solve(n, m));
    }
    return 0;
}
