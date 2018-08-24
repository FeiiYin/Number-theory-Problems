/*
 * @Samaritan_infi
 */
/// codeforce 1025 D 区间dp
/// 非常难思维到
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1005;
int GCD(int a, int b) {
    return (! b) ? a : GCD(b, a % b);
}

int dp[N][N][2];
/// dp[i][j][1] [i, j] 是 j 的左子树
/// dp[i][j][0] [i, j] 是 i 的右子树
int gcd[N][N];
int arr[N];

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; i ++)
        scanf("%d", &arr[i]);
    for (int i = 1; i <= n; i ++)
        for (int j = 1; j < i; j ++) {
            gcd[j][i] = gcd[i][j] = (GCD(arr[i], arr[j]) != 1);
        }
//    for (int i = 1; i <= n; i ++) {
//        for (int j = 1; j <= n; j ++)
//            cout << gcd[i][j] << " ";
//        cout << endl;
//    }
    for (int i = 1; i <= n; i ++)
        dp[i][i][0] = dp[i][i][1] = 1;
    for (int len = 1; len <= n; len ++) {
        for (int i = 1, j; i <= n; i ++) {
            j = i + len - 1;
            if (j > n) continue;
            for (int k = i + 1; k <= j; k ++)
                dp[i][j][0] |= (gcd[i][k] && dp[i + 1][k][1] && dp[k][j][0]);
            for (int k = i; k <= j - 1; k ++)
                dp[i][j][1] |= (gcd[k][j] && dp[i][k][1] && dp[k][j - 1][0]);
        }
    }
    bool flag = false;
    for (int i = 1; i <= n; i ++)
        if (dp[1][i][1] && dp[i][n][0]) {
            flag = true;
            break;
        }
    printf("%s\n", flag ? "Yes" : "No");
    return 0;
}


