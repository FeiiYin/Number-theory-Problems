/*
 * @Samaritan_infi
 */
/// 题意:求等比矩阵的和 poj3233， A^1+A^2+……+A^n(n到1e9)
/// 构造矩阵   A,E    的n次方等于  A^n,1+A^1+..A^(n-1)
///            0,E ,                0  , 1
//#include<bits/stdc++.h>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

#define rep(i,a,b) for(int i = (a); i <= (b); ++i)
const int N = 1e2 + 5;
int dim, mod;
struct Matrix {
    ll a[N][N];
    void init() { memset(a,0,sizeof(a)); }
    void show() { rep(i,1,dim) {rep(j,1,dim) printf("%lld ", a[i][j]); puts("");} }
};
Matrix mul(Matrix a, Matrix b) {
    Matrix ans; ans.init();
    rep(i,1,dim) rep(j,1,dim) rep(k,1,dim) ans.a[i][j] = (ans.a[i][j]+a.a[i][k]*b.a[k][j])%mod;
    return ans;
}
Matrix powmod(Matrix a, ll n) {
    Matrix ans; ans.init();
    if(! n) return ans;
    rep(i,1,dim) ans.a[i][i] = 1;
    while(n) {
        if(n & 1) ans = mul(ans,a);
        n >>= 1;
        a = mul(a, a);
    }
    return ans;
}

int main() {
    int n, k;
    Matrix ans;
    while (~ scanf("%d %d %d", &n, &k, &mod)) {
        dim = n << 1;
        ans.init();
        for (int i = 1; i <= n; i ++) for (int j = 1; j <= n; j ++)
            scanf("%lld", &ans.a[i][j]);
        for (int i = 1; i <= n; i ++)
            ans.a[i][n + i] = ans.a[n + i][n + i] = 1;
        ans = powmod(ans, k + 1);
        for (int i = 1; i <= n; i ++)
            (ans.a[i][n + i] += mod - 1) %= mod;
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j < n; j ++)
                printf("%lld ", ans.a[i][j + n]);
            printf("%lld\n", ans.a[i][dim]);
        }
    }
    return 0;
}
