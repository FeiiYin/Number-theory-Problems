/*
 * @Samaritan_infi
 * codeforces 645F 反演| 反贡献度.cpp
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 5;

int mu[N];
int prime[N], pcnt;
bool vis[N];
void Mobius () {
    mu[1] = 1;
    for (int i = 2; i < N; i++) {
        if (vis[i] == 0) {
            mu[i] = -1;
            prime[++pcnt] = i;
        }
        for (int j = 1; j <= pcnt && i * prime[j] < N; j++) {
            vis[i * prime[j]] = 1;
            if (i % prime[j] != 0)
                mu[i * prime[j]] = -mu[i];
            else {
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}
const int mod = 1e9 + 7;

#define inv(x) qpow(x, mod - 2)
inline int mul(int a, int b) { return ll(a) * b % mod; }
int qpow(int a, int b) { int r = 1; for (; b; b >>= 1) { if (b & 1) r = mul(r, a); a = mul(a, a); } return r; }
ll fac[N], inv_fac[N], inv[N];
void init_inv () {
    fac[0] = fac[1] = 1;
    for(int i = 2; i < N; i ++) {
        fac[i] = (fac[i - 1] * i) % mod;
        //inv[i] = (mod - mod / i) * inv[mod % i] % mod;/// ÄæÔª
    }
    inv_fac[N - 1] = inv(fac[N - 1]);
    for(int i = N - 2; i >= 0; i --)
        inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % mod;
}

inline int C(int a, int b) { return mul(fac[a], mul(inv_fac[a - b], inv_fac[b])); }

vector<int> factor[N];
ll contribution[N];
void init () {
    const int n = 1e6;
    memset(contribution, 0, sizeof contribution);
    for (int i = 1; i <= n; i ++) {
        for (int j = i; j <= n; j += i) {
            factor[j].push_back(i);
            /// j 这个数 对所有的因数 产生贡献 i * f[i] = i * sum(i | j) (mu[j/i] * F[j])
            /// 对于一个j来说 sum(i | j) ()
            (contribution[j] += mu[j/i] * i) %= mod;
            ///(contribution[j] += mu[i] * (j/i)) %= mod; morejarphone 代码 
        }
    }
}

ll cnt[N], F[N];
void solve (int n, int k, int q) {
    int x;
    const int N = 1e6;
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &x);
        for (int fac : factor[x]) cnt[fac] ++;
    }
    for (int i = 1; i <= N; i ++)
        F[i] = cnt[i] >= k ? C(cnt[i], k) : 0;
    ll ans = 0, temp;
    for (int i = 1; i <= N; i ++) {
        temp = 0;
        for (int j = i; j <= N; j += i)
            (temp += mu[j/i] * F[j]) %= mod;
        (ans += temp * i) %= mod;
    }
    ans = (ans % mod + mod) % mod;
    //cout << "ans : " << ans << endl;
    while (q --) {
        scanf("%d", &x);
        for (int fac : factor[x]) {
            cnt[fac] ++;
            temp = C(cnt[fac], k) - C(cnt[fac] - 1, k);
            (ans += temp * contribution[fac]) %= mod;
        }
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
}
int main () {
    Mobius();
    init_inv();
    init();
    int n, k, q; scanf("%d %d %d", &n, &k, &q);
    solve(n, k, q);
    return 0;
}
