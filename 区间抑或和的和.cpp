#include <bits/stdc++.h>
using namespace std ;

const int inf = 0x3f3f3f3f ;
const int maxn = 1e5 + 5 ;
int read[maxn] ;
int a[maxn] ;
int ans[4 * maxn] ;

int n ;

void dfs(int l , int r , int node ){
    if(l == r ){
        ans[node] = a[l] ;
        return ;
    }
    int mid = (l + r) >> 1 ;
    int num = 0 ;
    int left_0 = 0 ;
    int left_1 = 0 ;
    for(int i = mid ; i >= l ; i -- ){
        if(a[i] & 1){
            num ++ ;
        }
        if(num & 1){
            left_1 ++ ;
        }else
            left_0 ++ ;
    }

    num = 0 ;
    int right_0 = 0 ;
    int right_1 = 0 ;
    for(int i = mid + 1 ; i <= r ; i ++ ){
        if(a[i] & 1)
            num ++ ;
        if(num & 1)
            right_1 ++ ;
        else
            right_0 ++ ;
    }
    ans[node] = left_0 * right_1 + left_1 * right_0 ;

    dfs(l , mid , node << 1 ) ;
    dfs(mid + 1 , r , node << 1 | 1) ;

    ans[node] += ans[node<<1] + ans[node<<1|1] ;

}

int main(){

    while( ~ scanf("%d" , &n)){
        memset(ans , 0 , sizeof(ans )) ;
        for(int i = 0 ; i < n ; i ++ ){
            scanf("%d" , &read[i]) ;
        }
        int out = 0 ;

        for(int bit = 0 ; bit <= 14 ; bit ++ ){
            for(int i = 0 ; i < n ; i ++ ){
                a[i] = (read[i]>>bit) & 1  ;
            }
            memset(ans , 0 , sizeof(ans)) ;
            dfs(0 , n - 1 , 1 ) ;
            out += ans[1] << bit ;
        }

        printf("%d\n" , out) ;
    }
    return 0 ;
}
