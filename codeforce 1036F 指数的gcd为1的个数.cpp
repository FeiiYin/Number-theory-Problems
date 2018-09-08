/*
 * @Samaritan_infi
 */
/// 指数的gcd为1的个数 n 1e18
/// 注意直接快速幂不mod 会炸，只要判断是否大于n，所以如果炸的时候返回inf
/// 注意大的时候pow的精度问题
#include<bits/stdc++.h>
typedef long long ll;

const double eps = 1e-4;
const int N = 100;
int mu[N];
int prime[N], pcnt;
bool vis[N];
void Mobius () {
    mu[1] = 1;
    pcnt = 0;
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
    //for (int i = 2; i < N; i++) mu[i] += mu[i - 1];
}


const ll inf=2e18;
inline ll mmul(ll a, ll b){
    if(!a or !b) return 0;
    if(a < inf / b) return a * b;
    return inf;
}
ll quick_pow(ll a, ll b) {
    ll ans = 1, base = a;
    while (b) {
        if (b & 1) ans = mmul(ans, base);
        base = mmul(base, base);
        b >>= 1;
    }
    return ans;
}

ll cnt[N];
void work(ll n) {
    memset(cnt, 0, sizeof cnt);
    cnt[1] = n - 1;
    for (int i = 2; i <= 60; i ++) {

        ll temp = cnt[i - 1] + 1;
        if(temp <= 10){
            while(quick_pow(temp, i) > n) temp --;
            if(temp < 2) break;
            cnt[i] = temp - 1;
            continue;
        }
        cnt[i] = pow(n, 1.0 / i);
        while(quick_pow(cnt[i], i) <= n) cnt[i] ++;
        cnt[i] --;
        cnt[i] --;
    }

    ll ans = 0;
    for (int i = 1; i <= 60; i ++)
        ans += cnt[i] * mu[i];
    printf("%lld\n", ans);
}

int main () {
    ll n;
    Mobius();
    int _; scanf("%d", &_);
    while (_ --) {
        scanf("%lld", &n);
        work(n);
    }
    return 0;
}
