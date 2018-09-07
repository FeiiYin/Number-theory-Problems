/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;

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

int arr[N];
int main()
{
    int n;
    Mobius();
    while (cin >> n) {
        int ans = 0;
        int num = 0;
        /// 不含平方因子的个数
        for (int i = 1; i <= sqrt(n); i ++) {
            ans += mu[i] * (n / (i * i));
            //cout <<"temp : " << ans << endl;
        }
        cout << ans << endl;
        int a = 0;
        for (int i = 2; i <= sqrt(n); i ++) arr[num ++] = i * i;
        for (int i = 1; i <= n; i ++) {
            for (int j = 0; j < num; j ++)
                if (i % arr[j] == 0) { a ++; break; }
        }
        cout << n - a << endl;
    }
    return 0;
}
