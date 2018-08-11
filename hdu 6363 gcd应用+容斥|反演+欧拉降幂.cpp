/*
 * @Samaritan_infi
 */
///   gcd( 2^fib(i) - 1, 2^fib(j) - 1 )
/// = 2^gcd(fib(i), fib(j)) - 1
/// = 2^fib( gcd(i, j) ) - 1


#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2e6 + 5;
const int mod = 1e9 + 7;

#define inv(x) qpow(x, mod - 2)
inline int add(int a, int b) { if ((a += b) >= mod) a -= mod; return a; }
inline int mul(int a, int b) { return ll(a) * b % mod; }
int qpow(int a, int b) { int r = 1; for (; b; b >>= 1) { if (b & 1) r = mul(r, a); a = mul(a, a); } return r; }

ll fib[N];
ll fac[N], inv_fac[N];

void init(){
    fib[1] = fib[2] = 1;
    /// 欧拉降幂，指数上 % fai(p) - 1
    for(int i = 3; i < N; i ++) fib[i] = (fib[i - 2] + fib[i - 1]) % (mod - 1);
    fac[0] = fac[1] = 1;


    for(int i = 2; i < N; i ++) {
        fac[i] = (fac[i - 1] * i) % mod;
        //inv[i] = (mod - mod / i) * inv[mod % i] % mod; 逆元
    }
    inv_fac[N - 1] = inv(fac[N - 1]);
    for(int i = N - 2; i >= 0; i --)
        inv_fac[i] = (inv_fac[i + 1] * (i + 1)) % mod;
}

inline int C(int a, int b) {
    return mul(fac[a], mul(inv_fac[a - b], inv_fac[b]));
}

inline int BeautyCal(int g) {
    /// 欧拉降幂
    return add(qpow(2, fib[g] + (g < 47 ? 0 : mod - 1)), - 1 + mod);
}

ll num[N];

void work(){
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> factor;
    for(int i = 1; i * i <= n; i ++)
        if(n % i == 0) {
            factor.emplace_back(i);
            if(i * i < n) factor.emplace_back(n / i);
        }
    sort(factor.begin(), factor.end());

    ll ans = 0;
    for(int i = factor.size() - 1; i >= 0; i --) {
        int now_factor = factor[i];
        /// a 个东西分到 k 个地方 C(a + k - 1, k - 1)
        num[i] = C(n / factor[i] + k - 1, k - 1);
        for(int j = i + 1; j < factor.size(); j ++)
            if(factor[j] % factor[i] == 0)
                num[i] = add(num[i], mod - num[j]);
        ans = add(ans, mul(BeautyCal(now_factor), num[i]));
    }
    /// 除以总数求期望
    ans = mul(ans, inv(C(n + k - 1, k - 1))) % mod;
    printf("%lld\n", ans);
}

int main() {
    init();
    int kase;
    scanf("%d", &kase);
    while(kase --) work();
    return 0;
}
