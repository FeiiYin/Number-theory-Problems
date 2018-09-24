/*
 * @Samaritan_infi
 */
/// 题意:给出gcd和lcm，求a,b且使a+b最小
/// a*b/gcd = lcm -> (a/gcd)*(b/gcd)=(lcm/gcd),枚举其互质的两个因数使最小
#include <iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
LL m,n,ansn,ansm;
LL gcd(LL a,LL b){
    if (a==0) return 1;
    if(a<0) return gcd(-a,b);
    if(b==0) return a;
    return gcd(b,a%b);
}
LL modmult(LL a,LL b,LL n)//a*b%n
{
    a%=n; LL ret;
    for(ret=0; b; a=(a<<1)%n,b>>=1) if(b&1) 
        ret=(ret+a)%n;
    return ret;
}
LL modular(LL a,LL b,LL n)//renturn a^b%n
{
    LL ans=1; a%=n;
    while(b) {
        if(b&1) ans=modmult(ans,a,n),b--;
        b>>=1; a=modmult(a,a,n);
    }
    return ans;
}
bool witness(LL a,LL n)//判断 a^(n-1)=1(mod n)
{
    int t=0;
    LL x,xi,temp=n-1;
    while(temp%2==0)
        t++,temp/=2;
    xi=x=modular(a,temp,n);
    for(int i=1; i<=t; i++) {
        xi=modmult(xi,xi,n);
        if(xi==1&&x!=1&&x!=n-1) return 1;
        x=xi;
    }
    if(xi!=1) return 1;
    return 0;
}
bool millar_rabin(LL n,int s) {
    for(int j=1; j<=s; j++) {
        LL a=rand()%(n-1)+1;//a=rand()%(Y-X+1)+X; /*n为X~Y之间的随机数
        if(witness(a,n)) return 0;
    }
    return 1;
}
LL pollard_rho(LL n,LL c) {
    LL i=1,k=2,x,y; x=rand()%n; y=x;
    while(1) {
        i++; x=(modmult(x,x,n)+c)%n;
        LL d=gcd(y-x,n);
        if(d!=1&&d!=n) return d;
        if(x==y) return n;
        if(i==k) { y=x; k+=k; }
    }
}
LL factor[1000];
int tol;
void findfac(LL n) {
    if(millar_rabin(n,10)) { factor[tol++]=n; return; }
    LL p=n;
    while(p>=n) p=pollard_rho(p,rand()%(n-1)+1);
    findfac(p); findfac(n/p);
}
void dfs(LL s,LL now) {
    if(s==tol) {
        if(gcd(now,m/now)==1&&now+m/now<ansm+ansn)
            ansm=now,ansn=m/now;
        return;
    }
    dfs(s+1,now*factor[s]);
    dfs(s+1,now);
}
int main() {
    LL gcdx, lcm;
    while(~scanf("%lld%lld",&gcdx,&lcm)) {
        if(gcdx==lcm) {
            cout<<gcdx<<" "<<lcm<<endl;
            continue;
        }
        tol=0; lcm/=gcdx;
        findfac(lcm);
        m = n = 1;
        sort(factor,factor+tol);
        for(int i=0; i<tol; i++) m*=factor[i];
        ansn=n,ansm=m;
        dfs(0,1);
        if(ansn>ansm) swap(ansn,ansm);
        printf("%lld %lld\n",ansn*gcdx,ansm*gcdx);
    }
    return 0;
}
