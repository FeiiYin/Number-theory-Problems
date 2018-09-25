/*
 * @Samaritan_infi
 */
/// 题意: 欧拉公式，求fai(x)满足条件的最小因数
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
/// 求 n 的 欧拉值 O(log n)
void fai (int n) {
    int ans = n;
    for (int i = 2; i * i <= n; i ++) if (! (n % i)) {
        ans = ans - ans / i;
        do { n /= i; } while (! (n % i));
    }
    if (n > 1) ans = ans - ans / n;
    return ans;
}
/// 求 fai(x) 的最小因数满足 cal() 同余
prime[50][2] /// prime[i][0] 素因子， prime[i][1] 个数
ans = fai(x);
for (int i = 0; i < prime_number; i ++) {
    for (int j = 0; j < prime[i][1]; j ++) {
        if (cal( ... , ans / prime[i][0]) != 1) break;
        ans /= prime[i][0];
    }
}
return ans;
