/*
 * @Samaritan_infi
 * https://www.nowcoder.com/acm/contest/161/C
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e2 + 15;
const int M = 5e5 + 15;
const int mod = 1e9 + 7;

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)    return (x=1,y=0,a);
    if(a==0)    return (x=0,y=1,b);
    ll r=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return r;
}
int inv_cal(ll a,ll b)
{
    ll x,y;
    exgcd(a,b,x,y);
    x%=b;
    while(x<0)  x+=b;
    return x;
}

const int inv100 = inv_cal(100, mod);
ll m[N], r[N], p[N];
ll f[M], g[M];

int main() {
    int n, L, M;
    scanf("%d %d %d", &n, &L, &M);
    for (int i = 0; i < n; i ++) {
        scanf("%lld %lld %lld", &m[i], &r[i], &p[i]);
        r[i] = r[i] * inv100 % mod;
        p[i] = p[i] * inv100 % mod;
    }
    f[0] = 1;
    ll sum = 0;
    ll prop;
    for (int i = 0; i < n; i ++) {
        sum += m[i];
        for (int j = sum; j >= 0; j --) {
            f[j] = f[j] * (1 - p[i] + mod) % mod;
            g[j] = g[j] * (1 - p[i] + mod) % mod;
            if (j >= m[i]) {
                prop = f[ j - m[i] ] * p[i] % mod;
                f[j] = (f[j] + prop) % mod;
                g[j] = (g[j] + (g[ j - m[i] ] + m[i] * r[i] % mod * f[ j - m[i] ] % mod) * p[i]) % mod;
            }
        }
    }
    ll ans = 0;
    for (int i = L; i <= sum; i ++) {
        //cout << f[i] << " " << g[i] << endl;
        ans = (ans + M * f[i] - g[i]) % mod;
    }
    printf("%lld\n", ((ans % mod) + mod) % mod);
    return 0;
}
