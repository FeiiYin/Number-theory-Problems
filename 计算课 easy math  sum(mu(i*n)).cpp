/*
 * @Samaritan_infi
 * sum(1, m) (mu[i*n]) 
 * n square  ans = 0
 * n free square 
 * 枚举n的所有质因数d
 * 如果i和d互质，则有 sum(1, m) (mu[i*n]) = mu[d] * sum(1, m) (mu[i*n/d]) (mu[d] = -1)
 * 补上i和d不互质的部分 + sum(1, m / d) (mu[i * (n/d * d)]) = (mu[i * n])
 *
 * 直接推 sum(1, m) (mu[i*n]) = mu[n] * sum(d|n) (mu[d] * sum(1, m/d) (mu[i * d]))
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7 + 5;

int mu[N];
ll prime[N];int pcnt;
bool vis[N];
ll sum_mu[N];
void Mobius () {
    mu[1] = 1; pcnt = 0;
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
    sum_mu[1] = 1;
    for (int i = 2; i < N; i++) sum_mu[i] = sum_mu[i - 1] + mu[i];
}

const int M = 1e6 + 7;
struct hash_node {
    ll key;
    int next; ll val;
    hash_node () {}
    hash_node (ll a, int b, ll c) {
        key = a; next = b; val = c;
    }
} pq[M];
int head[M], tot;

void init() {
    tot = 0;
    memset(head, -1, sizeof head);
}

void add (ll key, ll val) {
    int pos = key % M;
    pq[tot] = hash_node(key, head[pos], val);
    head[pos] = tot ++;
}

ll cal(ll x) {
    if (x < N) return sum_mu[x];
    int pos = x % M;
    for (int i = head[pos]; ~ i; i = pq[i].next) {
        if (pq[i].key == x) return pq[i].val;
    }
    ll ans = 0;
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans += (r - l + 1) * cal(x / l);
    }
    add (x, 1 - ans);
    return 1 - ans;
}

ll all_factor[5000], all_num;
ll mu_factor[5000];
vector<ll> factor; /// prime factor
int cal_mu (ll n) {
    factor.clear();
    for (int i = 1; i <= pcnt; i ++) {
        if (prime[i] > n) break;
        if (! (n % prime[i])) {
            factor.push_back(prime[i]);
            n /= prime[i];
            if (! (n % prime[i])) return 0;
        }
    }
    if (n > 1) factor.push_back(n);
    return factor.size() & 1 ? -1 : 1;
}

//ll work(ll m, ll n, int mask) {
//    if (! m) return 0;
//    if (m == 1) return mu_factor[mask];
//    if (n == 1 || mask == 0) return cal(m);
//    ll ans = 0;
//    for (int x = mask; x != 0; x = (x - 1) & mask) {
//        ans += work(m / all_factor[x], all_factor[x], x) * mu_factor[x];
//    }
//    return ans * mu_factor[mask];
//}

ll work(ll m, ll n) {
    if (! m) return 0;
    if (n == 1) return cal(m);
    for (int i = 1; prime[i] * prime[i] <= n; i ++) {
        if (! (n % prime[i]))
            return - work(m, n / prime[i]) + work(m / prime[i], n);
    }
    return - work(m, n / n) + work(m / n, n);
}


int main() {
    init();
    Mobius();
    ll m, n;
    while (~ scanf("%lld %lld", &m, &n)) {
        int n_mu = cal_mu(n);
        //if (! judge(n)) { puts("0"); continue; }
        if (! n_mu) { puts("0"); continue; }
//        int now_mu; all_num = 0;
//        for (int i = 0; i < (1 << factor.size()); i ++) {
//            all_factor[i] = mu_factor[i] = 1;
//            for (int j = 0; j < factor.size(); j ++) if (i & (1 << j)) {
//                all_factor[i] *= factor[j];
//                mu_factor[i] *= -1;
//            }
//        }
        printf("%lld\n", work(m, n));
    }
    return 0;
}
