/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e7 + 5;

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

int sum[N];
void seive () {
    int n = 1e7, k;
    for (int i = 1; i * i <= n; i ++) {
        k = i * i;
        for (int j = k; j <= n; j += k)
            sum[j] += mu[j / k];
    }
    for (int i = 2; i <= n; i ++)
        sum[i] += sum[i - 1];
}


int main() {
    int kase; scanf("%d", &kase);
    Mobius();
    seive();
    while (kase --) {
        ll n, m; scanf("%lld %lld", &n, &m);
        if (n > m) swap(n, m);
        ll ans = 0, temp;
        for (ll l = 1, r; l <= n; l = r + 1) {
            r = min(n / (n / l), m / (m / l));
            //cout << l << " " << r << endl;
            ans += 1LL * (n / l) * (m / l) * (sum[r] - sum[l - 1]);
        }
        printf("%lld\n", n * m - ans);
    }
    return 0;
}
