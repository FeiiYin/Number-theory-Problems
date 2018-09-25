/*
 * @Samaritan_infi
 */
/// 题意: 求大组合数的约数个数
/// 题解: 求组合数的各个阶乘，对阶乘进行分解
#include <cstdio>
using namespace std;
typedef long long LL;
const int N = 500;
bool vis[N]; int prime[N], pcnt;
void prime_cal () {
    const int n = 440; pcnt = 0;
    for (int i = 2; i < n; i++) {
        if (! vis[i]) prime[pcnt++] = i;
        for (int j = 0; j < pcnt && i * prime[j] < n; j++) {
            vis[i * prime[j]] = true;
            if (! (i % prime[j])) break;
        }
    }
}
/// 把阶乘分解成若干素数的乘积
int fac[N][100];
void fac_init() {
    const int n = 440;
    for (int i = 0; i < pcnt; i++) for (int j = 2; j < n; j++)
        fac[j][i] = j / prime[i] + fac[j / prime[i]][i];
}
/// 求解组合数的因子个数
LL C_num[N][N];
void C_init () {
    const int n = 432;
    for (int i = 2; i < n; i++) for (int j = 1; j < i; j++) {
        C_num[i][j] = 1;
        for (int k = 0; k < pcnt && fac[i][k]; k++) {
            int side = fac[i][k] - fac[j][k] - fac[i - j][k];
            if (side) C_num[i][j] *= (side + 1);
        }
    }
}
int main () {
    prime_cal(); fac_init(); C_init();
    int n, x;  while (~ scanf("%d %d", &n, &x)) {
        if (! x || x == n) puts("1");
        else printf("%lld\n", C_num[n][x]);
    }
    return 0;
}
