/*
 * @Samaritan_infi
 * a^n + b^n = c^n 给出a，n构造b，c
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 1e9;

map<int, int> pq;

int main() {
    int kase;
    scanf("%d", &kase);
    while(kase --) {
        ll n, a, b, c;
        scanf("%lld %lld", &n, &a);
        if(n >= 3) {
            printf("-1 -1\n");
            continue;
        }
        if(n == 0) {
            printf("-1 -1\n");
            continue;
        }
        if(n == 1) {
            printf("%lld %lld\n", 1LL, 1LL + a);
            continue;
        }
        if(n == 2) {
            if(a == 1) {
                b = c = -1;
            } else if(a == 2) {
                b = c = -1;
            } else if(a == 3) {
                b = 4;
                c = 5;
            } else {
                if(a & 1) {
                    b = (a * a - 1) / 2;
                    c = (a * a + 1) / 2;
                } else {
                    if(a * a / 2 % 2 != 0) {
                        b = -1;
                        c = -1;
                    } else {
                        b = (a * a / 2 - 2) / 2;
                        c = (a * a / 2 + 2) / 2;
                    }
                }
            }
            if(b > N || c > N) { b = -1, c = -1; }
            printf("%lld %lld\n", b, c);

        }
    }
    return 0;
}
