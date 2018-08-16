/*
 * @Samaritan_infi
 */
/// 注意解的存储

#include <bits/stdc++.h>
using namespace std;
typedef long long ll ;

const int maxn = 55 ;
const int mod = 2 ;

int a[maxn][maxn] ;//增广矩阵
int x[maxn] ;

int gcd(int a , int b) {
    if(b == 0) return a; else return gcd(b , a % b) ;
}
inline int lcm(int a , int b) {
    return a / gcd(a , b) * b ;//先除后乘防溢出
}
int ex_gcd(int a , int b , int &x , int &y) {
    if(! b) {
        x = 1 ; y = 0 ;
        return a ;
    }else {
        int r = ex_gcd(b , a % b , y , x) ;
        y -= x * (a / b) ;
        return r ;
    }
}

int Gauss(int equ , int var) {
    int r , c ;
    for(r = 0 , c = 0 ; r < equ && c < var ; c ++) {
        int max_r = r ;
        for(int i = r + 1 ; i < equ ; i ++)
            if(abs(a[i][c] > abs(a[max_r][c])))
                max_r = i ;
        if(max_r != r)
            for(int i = c ; i <= var ; i ++)
                swap(a[r][i] , a[max_r][i]) ;
        if(! a[r][c]) continue ;

        for(int i = r + 1 ; i < equ ; i ++)
            if(a[i][c]) {
                int d = lcm(a[i][c] , a[r][c]) ;
                int t1 = d / a[i][c] , t2 = d / a[r][c] ;
                for(int j = c ; j <= var ; j ++) {
                    a[i][j] = ((a[i][j] * t1 - a[r][j] * t2) % mod + mod) % mod ;
                }
            }
        r ++ ;
    }
    for(int i = r ; i < equ ; i ++) if(a[i][var]) return -1 ;

    for(int i = r - 1 ; i >= 0 ; i --) {
        x[i] = a[i][var] ;
        for(int j = i + 1 ; j < var ; j ++) {
            x[i] = ((x[i] - a[i][j] * x[j]) % mod + mod) % mod ;
        }
        int x1 = 0 , y1 = 0 ;
        int d = ex_gcd(a[i][i] , mod , x1 , y1) ;
        x1 = ((x1 % mod) + mod) % mod ;
        x[i] = x[i] * x1 % mod ;
    }
    return var - r ;
}


int save[maxn][maxn] ;
int main() {
    int i, j;
    int equ , var ;
    int kase ; scanf("%d" , &kase) ;
    int tt = 1 ;
    while(kase --) {
        int n , m ;
        scanf("%d %d" , &n , &m) ;
        memset(save , 0 , sizeof save) ;
        for(int i = 0 ; i < m ; i ++) {
            int k , x ; scanf("%d" , &k) ;
            while(k --) {
                scanf("%d" , &x) ;
                save[x - 1][i] = 1 ;
            }
        }
        int op , x ; scanf("%d" , &op) ;
        printf("Case %d:\n" , tt ++) ;
        while(op --) {
            for(int i = 0 ; i < n ; i ++) {
                for(int j = 0 ; j < m ; j ++) {
                    a[i][j] = save[i][j] ;
                }
            }
            for(int i = 0 ; i < n ; i ++) {
                scanf("%d" , &x) ;
                a[i][m] = x ;
            }
            int free_num = Gauss(n , m) ;
            /*for(int i = 0 ; i < n ; i ++) {
                for(int j = 0 ; j <= m ; j ++) {
                    cout << a[i][j] << " " ;
                }cout << endl ;
            }*/
            if(free_num == -1) puts("0") ;
            else
            printf("%lld\n" , 1LL << free_num) ;
        }
    }
    return 0 ;
}
