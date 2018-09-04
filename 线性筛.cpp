线性筛素数
保证每个数只会被它的最小质因子给筛掉（不同于埃氏筛中每个数会被它所有质因子筛一遍从而使复杂度过高）
int pri[N],tot,zhi[N];//zhi[i]为1的表示不是质数
void sieve()
{
    zhi[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!zhi[i]) pri[++tot]=i;
        for (int j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            zhi[i*pri[j]]=1;
            if (i%pri[j]==0) break;
        }
    }
}
所有线性筛积性函数都必须基于线性筛素数。
线性筛莫比乌斯函数
int mu[N],pri[N],tot,zhi[N];
void sieve()
{
    zhi[1]=mu[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!zhi[i]) pri[++tot]=i,mu[i]=-1;
        for (int j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            zhi[i*pri[j]]=1;
            if (i%pri[j]) mu[i*pri[j]]=-mu[i];
            else {mu[i*pri[j]]=0;break;}
        }
    }
}
线性筛欧拉函数
int phi[N],pri[N],tot,zhi[N];
void sieve()
{
    zhi[1]=phi[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!zhi[i]) pri[++tot]=i,phi[i]=i-1;
        for (int j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            zhi[i*pri[j]]=1;
            if (i%pri[j]) phi[i*pri[j]]=phi[i]*phi[pri[j]];
            else {phi[i*pri[j]]=phi[i]*pri[j];break;}
        }
    }
}
线性筛约数个数
记d(i)
d(i)表示i的约数个数,d(i)=∏k (i=1)(ai+1)   d(i)=∏i=1k(ai+1)
维护每一个数的最小值因子出现的次数（即a1）即可
int d[N],a[N],pri[N],tot,zhi[N];
void sieve()
{
    zhi[1]=d[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!zhi[i]) pri[++tot]=i,d[i]=2,a[i]=1;
        for (int j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            zhi[i*pri[j]]=1;
            if (i%pri[j]) d[i*pri[j]]=d[i]*d[pri[j]],a[i*pri[j]]=1;
            else {d[i*pri[j]]=d[i]/(a[i]+1)*(a[i]+2);a[i*pri[j]]=a[i]+1;break;}
        }
    }
}
线性筛约数和
记σ(i) σ(i)表示i的约数和
σ(i)=∏k i=1(∑aij=0 pj i)   σ(i)=∏i=1k(∑j=0aipij)
维护low(i) low(i)表示i的最小质因子的指数次幂，即pa1 1 p1a1，sum(i)
sum(i)表示i的最小质因子对答案的贡献，即∑a1 j=0 pj 1 ∑j=0a1p1j
（这玩意儿可能会爆int吧，我这里就不管那么多了）
int low[N],sum[N],sigma[N],pri[N],tot,zhi[N];
void sieve()
{
    zhi[1]=low[1]=sum[1]=sigma[1]=1;
    for (int i=2;i<=n;i++)
    {
        if (!zhi[i]) low[i]=pri[++tot]=i,sum[i]=sigma[i]=i+1;
        for (int j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            zhi[i*pri[j]]=1;
            if (i%pri[j]==0) 
            {
                low[i*pri[j]]=low[i]*pri[j];
                sum[i*pri[j]]=sum[i]+low[i*pri[j]];
                sigma[i*pri[j]]=sigma[i]/sum[i]*sum[i*pri[j]];
                break;
            }
            low[i*pri[j]]=pri[j];
            sum[i*pri[j]]=pri[j]+1;
            sigma[i*pri[j]]=sigma[i]*sigma[pri[j]];
        }
    }
}
线性筛一般积性函数
若想线性筛出积性函数
f(x)
f(x)
，就必须能够快速计算出一下函数值：
1、
f(1)
f(1)

2、
f(p)
f(p)
（
p
p
是质数）
3、
f(
p
k
)
f(pk)
（
p
p
是质数）
其实就是含有的质因子数小于等于1的所有数对应的函数值。
常见的积性函数都会给出上述函数值的有关定义。对于自定义的一个积性函数（如狄利克雷卷积），就需要自行计算出上述函数值。
我们假设已经完成了上述函数值的计算，现在要求筛出所有至少含有两个质因子的数对应的函数值。
显然，一个含有至少两个质因子的数一定可以被分解成两个互质的且均不为1的数的乘积。此时我们就可以用
f(xy)=f(x)f(y)
f(xy)=f(x)f(y)
计算得出相应的函数值。
以下内容需要完全理解上面的线性筛素数。
我们考虑筛的过程中，
void sieve()
{
    zhi[1]=low[1]=1;
    f[1]=对1直接定义;
    for (ll i=2;i<=n;i++)
    {
        if (!zhi[i]) low[i]=pri[++tot]=i,f[i]=对质数直接定义;
        for (ll j=1;j<=tot&&i*pri[j]<=n;j++)
        {
            zhi[i*pri[j]]=1;
            if (i%pri[j]==0)
            {
                low[i*pri[j]]=low[i]*pri[j];
                if (low[i]==i)
                    f[i*pri[j]]=对质数的若干次幂进行定义(一般由f[i]递推);
                else
                    f[i*pri[j]]=f[i/low[i]]*f[low[i]*pri[j]];
                break;
            }
            low[i*pri[j]]=pri[j];
            f[i*pri[j]]=f[i]*f[pri[j]];
        }
    }
}
