
#include<bits/stdc++.h>
using namespace std;
#define maxn 2000100
long long Min(long long x,long long y){
    return x<y?x:y;
}
int mysqrt(long long n){
    int x=sqrt(n);
    while(x*(long long)x<n) x++;
    while(x*(long long)x>n) x--;//必须满足S是最大的满足S*S<=n的数
    return x;
}
int S;
long long g[maxn];
int prim[maxn],ilem;
long long n;
void getg(){
    S=mysqrt(n),ilem=0;
    long long *l=g+S,*s=g;
    for(int i=1;i<=S;i++)
        s[i]=i,l[i]=n/i;//s[i]->g(i),l[i]->g(n/i),此时g(i)代表不超过i的质数的数量(包括1)
    for(int p=2;p<=S;p++){
        if(s[p]==s[p-1]) continue;//p不是质数
        long long r=p*(long long)p,v=s[p-1];
        int ed1=S/p,ed2=Min(n/r,(long long)S);
        for(int i=1;i<=ed1;i++)
            l[i]-=l[i*p]-v;
        if(n/p<INT_MAX){
            int m=n/p;
            for(int i=ed1+1;i<=ed2;i++)
                l[i]-=s[m/i]-v;
        }
        else{
            long long m=n/p;
            for(int i=ed1+1;i<=ed2;i++)
                l[i]-=s[m/i]-v;
        }
/*** 如果不这么写的话,常数大概会增加一倍左右.把int和long long分开在n=1e11的数据下有0.4s的优化(开O2) ***/
/*** 论减少除法数量的重要性... ***/
        for(int i=S;i>=r;i--)
            s[i]-=s[i/p]-v;
        prim[++ilem]=p;
    }
    prim[++ilem]=S+1;//这句很容易被遗漏
    for(int i=1;i<=S;i++)
        s[i]=s[i]*4,l[i]=l[i]*4;
}
long long F(long long x,int y){
    if(prim[y]>x) return 0;
    long long res=g[x<=S?x:S+n/x]-g[prim[y]-1],st;
    for(int i=y;i<=ilem;i++){
        st=prim[i];
        if(st*(long long)prim[i]>x) break;
        for(int j=1;;j++){
            if(st*prim[i]>x) break;
            res+=F(x/st,i+1)*(j*3+1)+(j*3+4);
            st=st*prim[i];
        }
    }
    return res;
}
int main(){
//  freopen("DIVCNT3.in","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld",&n);
        getg();
        printf("%lld\n",F(n,1)+1);//注意把1的贡献算进来.
    }
    return 0;
}
