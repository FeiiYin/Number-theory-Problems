/*
 * @Samaritan_infi
 */
///  欧拉降幂  n^x % m == n^( fai(m) + x % fai(m) ) % m
///  条件  x > fai(m)

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;


#define Mod(a,b) a<b?a:a%b+b						//重定义取模，按照欧拉定理的条件
#define N 100010

ll n,q,mod,a[N];
map<ll,ll> mp;

ll qpow(ll x,ll n,ll mod) {
    ll res=1;
    while(n) {
        if (n&1) res=Mod(res*x,mod),n--;
        x=Mod(x*x,mod); n>>=1;
    }
    return res;
}

ll phi(ll k) {
    ll i,s=k,x=k;
    if (mp.count(k)) return mp[x];					//记忆化存储
    for(i = 2;i * i <= k; i++) {
        if(k % i == 0) s = s / i * (i - 1);
        while(k % i == 0) k /= i;
    }
    if(k > 1) s = s / k * (k - 1);
    mp[x]=s; return s;
}

ll solve(ll l,ll r,ll mod) {
    if (l==r||mod==1) return Mod(a[l],mod);					//如果到右端点或者φ值等于1，那么直接返回当前数字
    return qpow(a[l],solve(l+1,r,phi(mod)),mod);			//否则指数为[l+1,r]区间的结果
}

int main() {
    scanf("%lld%lld",&n,&mod);
    for(int i=1;i<=n;i++)
        scanf("%lld",&a[i]);
    scanf("%lld",&q);
    while(q--) {
        int L,R;
        scanf("%d%d",&L,&R);
        printf("%lld\n",solve(L,R,mod)%mod);				//对mod取模，因为qpow内部是用Mod(a,b)取模
    }
    return 0;
}
