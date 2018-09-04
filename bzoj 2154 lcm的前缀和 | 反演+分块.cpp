/*
 * @Samaritan_infi
 */
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#include<queue>
using namespace std;
#define MOD 20101009
#define MAX 12000000
#define ll long long
inline int read()
{
    int x=0,t=1;char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-')ch=getchar();
    if(ch=='-')t=-1,ch=getchar();
    while(ch<='9'&&ch>='0')x=x*10+ch-48,ch=getchar();
    return x*t;
}
int mu[MAX],pri[MAX],tot;
bool zs[MAX];
int n,m;
int G[MAX],ans;
int smu[MAX],sqr[MAX];
void Getmu()
{
    zs[1]=true;mu[1]=1;
    for(int i=2;i<=n;++i)
    {
        if(!zs[i]){pri[++tot]=i;mu[i]=-1;}
        for(int j=1;j<=tot&&i*pri[j]<=n;++j)
        {
            zs[i*pri[j]]=true;
            if(i%pri[j])mu[i*pri[j]]=-mu[i];
            else{mu[i*pri[j]]=0;break;}
        }
    }
    for(int i=1;i<=n;++i)smu[i]=(smu[i-1]+mu[i]+MOD)%MOD;
}
int Solve(int xx,int yy)
{
    long long ans=0;
    //for(int i=1;i<=xx;++i)G[i]=1ll*i*i%MOD*1ll*(1ll*(1+xx/i)*(xx/i)/2%MOD)*(1ll*(1+yy/i)*(yy/i)/2%MOD)%MOD;
    //for(int i=1;i<=xx;++i)ans=(ans+1ll*mu[i]*G[i]%MOD+MOD)%MOD;
    int i=1,j;
    while(i<=xx)
    {
        j=min(xx/(xx/i),yy/(yy/i));
        int GG=1ll*(1ll*(1+xx/i)*(xx/i)/2%MOD)*(1ll*(1+yy/i)*(yy/i)/2%MOD)%MOD;
        ans+=1ll*(sqr[j]-sqr[i-1])%MOD*GG%MOD;
        ans%=MOD;
        i=j+1;
    }
    return (ans+MOD)%MOD;
}
int main()
{
    n=read();m=read();
    if(n>m)swap(n,m);
    Getmu();
    for(int i=1;i<=n;++i)sqr[i]=(sqr[i-1]+1ll*i*i%MOD*mu[i]%MOD+MOD)%MOD;
    //for(int i=1;i<=n;++i)ans=1ll*((ans+1ll*i*Solve(n/i,m/i))%MOD)%MOD;
    int i=1,j;
    while(i<=n)
    {
        j=min(n/(n/i),m/(m/i));
        int t=1ll*(i+j)*(j-i+1)/2%MOD;
        ans=(ans+1ll*Solve(n/i,m/i)*t%MOD)%MOD;
        i=j+1;
    }
    printf("%d\n",ans);
    return 0;
}
