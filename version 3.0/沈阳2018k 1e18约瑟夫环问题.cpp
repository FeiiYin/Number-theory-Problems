/*
 * @Samaritan_infi
 */
/// 题意: 超大约瑟夫环问题(min(m, k) < 2e6)
/// 题解: 分k=1，m小和k小的情况讨论
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 2e6 + 5;
int moni[N];

int main () {
    const int BLOCK = 2e6;
    int kase, _ = 1; scanf("%d", &kase);
    while (kase--) {
        LL n, m, k;
        scanf("%lld %lld %lld", &n, &m, &k);
        printf("Case #%d: ", _++);
        if (k == 1) {
            printf("%lld\n", m);
        } else if (m < BLOCK) {
            LL people = (k - 1) % (n - m + 1) + 1;
            /// from back -> origin
            /// dp[n-m+1][1] = k % (n-m+1)
            /// dp[n][m] = (dp[n-1][m-1] + k - 1) % n + 1
            for (int i = 2; i <= m; ++i)
                people = (people + k - 1) % (n - m + i) + 1;
            printf("%lld\n", people);
        } else {
            /// 加很多次才取mod
            /// 加 c+k*x > a+x -> x = (a-c)/(k-1)
            /// dp[a+x][b+x] = (dp[a][b] + k*x-1) % (a+x) + 1
            /// 还是从 dp[n-m+1][1]开始
            LL a = n - m + 1, b = 1, c = (k - 1) % a + 1;
            LL x = 0;
            while (b + x <= m) {
                a += x; b += x;
                c = (c + x * k - 1) % a + 1;
                x = (a - c) / (k - 1) + 1; /// 不加1为最后一个不取mod的
            }
            c = (c + (m - b) * k - 1) % n + 1;
            printf("%lld\n", c);
        }
    }
    return 0;
}
