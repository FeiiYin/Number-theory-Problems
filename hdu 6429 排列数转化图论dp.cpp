/*
 * @Samaritan_infi
 */

#include <bits/stdc++.h>
// 6429 排列数转化图论dp.cpp
/// 题目 1-n的排列的权值： sum(abs(pi - i))
/// 询问 n 个数的排列 权值 = s 的个数有多少个 s 从0 到 n*n-1

///考虑一个 n 个点的图, 其中点 i 向 pi 连边, 显然这张图是由若干个环组成的, 并且 排列的权值就是每条边的长度之和.
/// 考虑从前往后 DP. 设状态 dp(i,j,k) 表示考虑了前 i 个位置, 有 j 条出边连出, j 条 入边连入 1...i 这段前缀, 且当前的权值为 k.
/// 前面区间如果有i条边连入，则一定i条边连出 o(n4)

#define x first
#define y second
#define MP std::make_pair
#define SZ(x) ((int)(x).size())
#define ALL(x) (x).begin(), (x).end()
#define DEBUG(...) fprintf(stderr, __VA_ARGS__)
#ifdef __linux__
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif

using std::pair;
using std::vector;
using std::string;

typedef long long LL;
typedef pair<int, int> Pii;

const int oo = 0x3f3f3f3f;

template<typename T> inline bool chkmax(T &a, T b) { return a < b ? a = b, true : false; }
template<typename T> inline bool chkmin(T &a, T b) { return b < a ? a = b, true : false; }
// EOT

const int MAXN = 103;

int N, P;

inline void mod(int &x) { x = (x >= P ? x - P : x); }

void solve()
{
    static int f[MAXN][MAXN * MAXN], g[MAXN][MAXN * MAXN];

    memset(g, 0, sizeof(g));
    g[0][0] = g[1][0] = 1;
    for (int i = 1; i < N; ++i) {
        memcpy(f, g, sizeof(f));
        memset(g, 0, sizeof(g));
        for (int j = 0; j <= i; ++j) {
            for (int k = 0; k <= i * i; ++k) {
                if (!f[j][k]) continue;
                mod(g[j][k + j] += (LL)(2 * j + 1) * f[j][k] % P);
                if (j) mod(g[j - 1][k + j] += (LL)j * j * f[j][k] % P);
                mod(g[j + 1][k + j] += f[j][k]);
            }
        }
    }

    for (int i = 0; i < N * N; ++i) {
        int cur = i & 1 ? 0 : g[0][i / 2];
        printf("%d%c", cur, " \n"[i == N * N - 1]);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &N, &P);
        solve();
    }

    return 0;
}
