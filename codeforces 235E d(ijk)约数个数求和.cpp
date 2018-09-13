/*
 * @Samaritan_infi
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

/// d(i) : i的因数个数
/// d(n*m) = sum(i|n) sum(j|n) [gcd(i, j) == 1]
/// d(n*m*t) = sum(i|n) sum(j|m) sum(k|t) [gcd(i, j)==1][gcd(j, k)==1][gcd(i, k)==1]

const int N = 2e3 + 5;
const int mod = 1073741824;

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
}

int gcd[N][N];
int cal_gcd(int x, int y) {
    if (gcd[x][y]) return gcd[x][y];
    int r, X = x, Y = y;
    while (y) {
        r = x % y; x = y; y = r;
    }
    return gcd[X][Y] = x;
}

int cal (int n, int d, int k) {
    int ans = 0;
    for (int i = 1; i <= n; i ++) if (cal_gcd(d*i, k) == 1)
        ans += n / i;
    return ans;
}

/// 不能分块，因为条件里包含gcd (di, k) == 1
void solve (int n, int m, int t) {
    int ans = 0, temp;
    for (int k = 1; k <= t; k ++) {
        temp = 0;
        for (int d = 1; d <= n; d ++) if (mu[d]) {
            temp += mu[d] * cal(n / d, d, k) * cal(m / d, d, k);
        }
        ans += temp * (t / k);
    }
    printf("%d\n", (ans % mod + mod) % mod);
}

int main () {
    Mobius();
    int arr[3];
    scanf("%d %d %d", &arr[0], &arr[1], &arr[2]);
    sort(arr, arr + 3);
    solve(arr[0], arr[1], arr[2]);
    return 0;
}
