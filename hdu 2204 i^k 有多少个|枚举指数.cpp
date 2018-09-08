/*
 * @Samaritan_infi
 */
/// 1e18 中 i^k 有多少个 k > 1
/// 枚举指数，制数最多到60
#include<bits/stdc++.h>
typedef long long ll;

const int prime[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
const int len = 17;
const double eps = 1e-8;
ll ans, n;
int i;
void dfs(int cur, int num, int k) {
    if (! k) {
        ll temp = pow(n, 1.0 / num) + eps; /// 这样能避免大数开放的误差 = = 
        if (pow(temp, 0.0 + num) > n) temp --;
        temp --; /// 去掉 1
        if (temp > 0)
            ans += temp * (i & 1 ? 1 : -1);
        return;
    }
    if (cur >= len) return;
    if (num * prime[cur] < 60)
        dfs(cur + 1, num * prime[cur], k - 1);
    dfs(cur + 1, num, k);
}

void work() {
    ans = 0;
    for (i = 1; i <= 3; i ++)
        dfs(0, 1, i);
    printf("%lld\n", ans + 1); /// 补上 1
}

int main () {
    while (~ scanf("%lld", &n)) {
        work();
    }
    return 0;
}
