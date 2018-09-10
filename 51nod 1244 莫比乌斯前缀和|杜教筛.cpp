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
    for (int i = 2; i < N; i++) mu[i] += mu[i - 1];
}

const int M = 1e6 + 7;
struct hash_node {
    ll key;
    int next, val;
    hash_node () {}
    hash_node (ll a, int b, int c) {
        key = a; next = b; val = c;
    }
} pq[M];
int head[M], tot;

void init() {
    tot = 0;
    memset(head, -1, sizeof head);
}

void add (ll key, int val) {
    int pos = key % M;
    pq[tot] = hash_node(key, head[pos], val);
    head[pos] = tot ++;
}

int cal(ll x) {
    if (x < N) return mu[x];
    int pos = x % M;
    for (int i = head[pos]; ~ i; i = pq[i].next) {
        if (pq[i].key == x) return pq[i].val;
    }
    int ans = 0;
    for (ll l = 2, r; l <= x; l = r + 1) {
        r = x / (x / l);
        ans += (r - l + 1) * cal(x / l);
    }
    add (x, 1 - ans);
    return 1 - ans;
}

int main() {
    ll a, b;
    init();
    Mobius();
    while (~ scanf("%lld %lld", &a, &b)) {
        printf("%d\n", cal(b) - cal(a - 1));
    }
    return 0;
}
