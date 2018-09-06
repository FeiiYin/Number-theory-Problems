/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int N = 1e3 + 5;

const int MOD = 998244353;
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
LL mul(LL base, LL exp, LL mod)
{
    LL ret = 0;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            (ret += base) %= mod;
        (base += base) %= mod;
    }
    return ret;
}

LL fpm(LL base, LL exp, LL mod)
{
    LL ret = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            ret = mul(ret, base, mod);
        base = mul(base, base, mod);
    }
    return ret;
}

LL fpm(LL base, LL exp)
{
    LL ret = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1)
            (ret *= base) %= MOD;
        (base *= base) %= MOD;
    }
    return ret;
}

bool isprime(LL x)
{
    const int SIZE = 12;
    const int PRIMES[SIZE] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (x == 2) return true;
    if (x == 1 || !(x & 1)) return false;

    LL k = x - 1, t = 0;
    for (; !(k & 1); k >>= 1) ++t;
    for (int i = 0; i < SIZE && PRIMES[i] < x; ++i) {
        LL g = fpm(PRIMES[i], k, x);
        for (int j = 0; j < t; ++j) {
            LL g0 = mul(g, g, x);
            if (g0 == 1 && g != 1 && g != x - 1) return false;
            g = g0;
        }
        if (g != 1) return false;
    }
    return true;
}

vector<LL> pf;
LL totfactors, factors[75], fcnt[75];

#define F(t) ((mul(t, t, x) + c) % x)

void pollardRho(LL x)
{
    if (isprime(x)) {
        pf.push_back(x);
        return;
    }
    for (;;) {
        LL c = rand() % (x - 1) + 1;
        LL p = rand() % x, q = F(p);
        while (p != q) {
            LL d = std::__gcd(x, std::abs(p - q));
            if (d != 1) {
                pollardRho(d);
                pollardRho(x / d);
                return;
            }
            p = F(p); q = F(F(q));
        }
    }
}

void getPrimeFactors(LL x)
{
    pf.clear();
    pollardRho(x);
    std::sort(ALL(pf));
    assert(SZ(pf) >= 1);

    totfactors = 0;
    factors[totfactors] = pf[0];
    fcnt[totfactors] = 1;
    for (int i = 1; i < SZ(pf); ++i) {
        if (pf[i] == factors[totfactors])
            ++fcnt[totfactors];
        else {
            factors[++totfactors] = pf[i];
            fcnt[totfactors] = 1;
        }
    }
    ++totfactors;

     for (int i = 0; i < totfactors; ++i) {
         printf("(%lld,%lld),", factors[i], fcnt[i]);
     }
     puts("");
}

int main() {
    LL a;
    while(cin >> a) {
        getPrimeFactors(a);
    }
    return 0;
}
