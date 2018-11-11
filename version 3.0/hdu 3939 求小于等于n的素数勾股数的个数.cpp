#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long LL;
#define maxn 1000010
int phi[maxn]; //打欧拉表
int prime[maxn],cnt; //打素数表，并纪录10^6内的素数的个数
bool flag[maxn]; //flag[i]为0表示i为素数
int p[100],num; //纪录一个数的素因子，并纪录因子数num
LL ans,l; //ans为不超过l的毕达哥拉斯三元组的数目
 
void init()
{   //打素数表
    cnt=0;
    memset(flag,0,sizeof(flag));
    for(int i=2;i<maxn;i++)
      if(!flag[i])
      {
          prime[cnt++]=i;
          for(int j=i+i;j<maxn;j+=i)
              flag[j]=1;
      }
    //打欧拉表
    for(int i=0;i<maxn;i++) phi[i]=i;
    for(int i=2;i<maxn;i+=2) phi[i]>>=1;
    for(int i=3;i<maxn;i+=2)
      if(phi[i]==i)
        for(int j=i;j<maxn;j+=i)
          phi[j]=phi[j]-phi[j]/i;
}
 
void divide(int x)
{//分解质因子
    num=0;
    for(int i=0;i<cnt&&prime[i]*prime[i]<=x;i++)
      if(x%prime[i]==0)
      {
          p[num++]=prime[i];
          while(x%prime[i]==0) x/=prime[i];
      }
    if(x>1) p[num++]=x;
}
 
void dfs(int id,int mul,int tot,int x)
{//搜索[1,x]与m互素的数的个数
    if(id==num)
    {
        if(tot&1) ans=ans-x/mul;
        else ans=ans+x/mul;
        return ;
    }
    dfs(id+1,mul*p[id],tot+1,x);
    dfs(id+1,mul,tot,x);
}
 
int main()
{
    init();
    int t;
    cin>>t;
    while(t--)
    {
        scanf("%lld",&l);
        int temp=sqrt(l+0.0);
        ans=0;
        for(int i=1;i<=temp;i++) //枚举m
        {
            int lim=sqrt(l-(LL)i*i+0.0);  //m确定后n的最大值
            if(i&1) //m为奇数
            {
                divide(i);
                if(i<=lim) dfs(0,1,0,i>>1);
                else dfs(0,1,0,lim>>1);
            }
            else //m为偶数
            {
                if(i<=lim) ans+=phi[i];
                else
                {
                    divide(i);
                    dfs(0,1,0,lim);
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
