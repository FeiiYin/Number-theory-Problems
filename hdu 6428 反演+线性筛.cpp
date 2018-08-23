/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>

typedef long long i64;
typedef unsigned int u32;

static const int MAXN = 10000000 + 5;

int totp;
bool ish[MAXN];
int pri[MAXN];
int minp[MAXN];
int last[MAXN];
int count[MAXN];
//int mu[MAXN];
int mup[MAXN];
u32 limit2[MAXN];
u32 limit3[MAXN];

/// limit_k[d] 最小的 x 使得 d | x^k,
/// d = a1^p1 * a2^p2 * ...
/// limit_k[d] = a1^(p1/k) * a2^(p2/k) * ... 均为上取整
void euler(int N = MAXN) {
    int i, j;

    ish[1] = true;
    minp[1] = 1;
    last[1] = 1;
    count[1] = 0;
    mup[1] = 1;
    limit2[1] = 1;
    limit3[1] = 1;

    for (i = 2; i < N; ++ i) {
        if (!ish[i]) {
            pri[totp++] = i;
            minp[i] = i;
            last[i] = 1;
            count[i] = 1;
            mup[i] = i - 2;
            limit2[i] = i;
            limit3[i] = i;
        }

        for (j = 0; i * pri[j] < N; ++ j) {
            int x = i * pri[j];
            int p = pri[j];
            ish[x] = true;
            if (i % p == 0) {
                minp[x] = p;
                last[x] = last[i];
                count[x] = count[i] + 1;
                int pa = x / last[x];
                mup[x] = (pa - pa / p * 2 + pa / (p * p)) * mup[last[x]];
                limit2[x] = limit2[i];
                limit3[x] = limit3[i];
                if (count[x] % 2 == 1) limit2[x] *= p;
                if (count[x] % 3 == 1) limit3[x] *= p;
                break;
            } else {
                minp[x] = p;
                last[x] = i;
                count[x] = 1;
                mup[x] = (p - 2) * mup[i];
                limit2[x] = p * limit2[i];
                limit3[x] = p * limit3[i];
            }
        }
    }
}

void exec() {
    u32 A, B, C, i, sum(0);
    //std::cin >> A >> B >> C;
    scanf("%d %d %d", &A, &B, &C);
    for (i = 1; i <= A; ++ i)
        sum += (A / i) * (B / limit2[i]) * (C / limit3[i]) * mup[i];
    printf("%d\n", (sum & ((1 << 30) - 1)));
    //std::cout << (sum & ((1 << 30) - 1)) << '\n';
}

int main() {
#ifdef __DEBUG
    freopen("std.in", "r", stdin);
    freopen("std.out", "w", stdout);
#endif
    euler();

    int t;
    scanf("%d", &t);
    while (t --)
        exec();
    return 0;
}
