#include <cstdio>
#define LL __int64
const LL mm=1000000007;
LL mod, pow[10005];
int n, m;
LL gcd(LL a, LL b){
    return b==0 ? a : gcd(b,a%b);
}
LL rotat()     //旋转时的不动点
{
    LL ans = 0;
    for (int i=0; i<m; ++i)
        ans = (ans+pow[gcd(i,m)]) % mod;
    return ans;
}
LL overturn()  //翻转时的不动点，分奇偶讨论
{
    LL ans = 0;
    if(m & 1)
        ans = (ans+m*pow[(m+1)/2]) % mod;
    else
        ans = (ans+m/2*(pow[m/2+1]+pow[m/2])) % mod;
    return ans;
}
int main (){
    int cas, t=0;
    scanf("%d", &cas);
    while(cas--)    {
        LL ans = 0;
        scanf("%d%d", &n, &m);
        mod = 2*m*mm;
        pow[0] = 1;
        for(int i=1; i<=m; ++i)
            pow[i] = (pow[i-1]*n) % mod;
        ans += rotat();
        ans  = (ans + overturn()) % mod;
        printf("Case #%d: %I64d\n", ++t, (ans/2/m)%mm);
    }
    return 0;
}
