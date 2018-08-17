/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e6 + 5;
int mod = 1e9 + 7;
//#define inv(x) qpow(x, mod - 2)

ll quick_pow(ll a, ll x, ll mod) {
    ll ans = 1;
    while(x) {
        if(x & 1) ans = (ans * a) % mod;
        a = (a * a) % mod;
        x >>= 1;
    }
    return ans % mod;
}

ll exgcd(ll a,ll b,ll &x,ll &y)
{
    if(b==0)    return (x=1,y=0,a);
    if(a==0)    return (x=0,y=1,b);
    ll r=exgcd(b,a%b,y,x);
    y-=(a/b)*x;
    return r;
}
int mul_1(ll a,ll b)
{
    ll x,y;
    exgcd(a,b,x,y);
    x%=b;
    while(x<0)  x+=b;
    return x;
}

/// 同时求欧拉函数和莫比乌斯函数的板子
int fac[N],miu[N],phi[N];//f[N],F[N];
void init() {
    for(int i=1;i<N;++i) fac[i]=i;
    phi[1]=miu[1]=1;
    for(int i=2;i<N;++i)
    {
        if(fac[i]==i)
            for(int j=i<<1;j<N;j+=i)
                fac[j]=i;
        if(i/fac[i]%fac[i]) phi[i]=(fac[i]-1)*phi[i/fac[i]],miu[i]=-miu[i/fac[i]];
        else phi[i]=fac[i]*phi[i/fac[i]],miu[i]=0;
    }
}

ll F[N], f[N];

int main() {
    init();
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        /// gu(a, b) = gcd(a, b) / fai(gcd(a, b))
        /// F(g) = (n / g) * (m / g)
        /// f(g) = sum( mu(a) * F(a * g) )
        int n, m, p;
        scanf("%d %d %d", &n, &m, &p);
        mod = p;
        if(n > m) swap(n, m);
        ll ans = 0, fg;
        for(int i = 1; i <= n; i ++) F[i] = (ll)(n / i) * (m / i) % p;
        for(int i = 1; i <= n; i ++) {
            fg = 0;
            for(int j = i; j <= n; j += i) {
                fg += F[j] * miu[j / i];
            }  //ans=(1ll*ans+1ll*i*mul_1(phi[i],MOD)%MOD*f[i])%MOD;
            fg %= p;
            ans = (ll)(fg * i % mod * mul_1(phi[i], p) % mod + ans) % mod;
            //cout << fg << " " << ans << endl;
        }
        ans = (ans % mod + mod) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}
