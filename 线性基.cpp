/*
 * @Samaritan_infi
 * https://vjudge.net/problem/UVALive-8522
 * 银牌提
 */
   所谓线性基，就是线性代数里面的概念。一组线性无关的向量便可以作为一组基底，张起一个线性的向量空间，这个基地又称之为线性基。
   这个线性基的基底进行线性运算，可以表示向量空间内的所有向量，也即所有向量可以拆成基底的线性组合。
       在ACM领域，线性基主要用来处理有关异或和的极值问题。根据异或按照二进制数位进行的方式，我们可以把一个数字拆成它的二进制表示形式，
       而这个二进制形式拆成一位一位的，可以用向量来表示。显然，一组线性无关的向量可以张起一个向量空间，
       我们同样可以考虑构造这样一组数字的二进制形式组成的线性基。在这个线性基里面，我可以通过基底的线性组合、异或运算，表示所有的异或结果。
       要构造这样的线性基，首先要满足一个性质：任取向量组中两个向量a、b，把其中一个替换成a xor b，这组向量线性组合得到的线性空间相同。
       这个性质对于xor来说是显然的，因为xor偶数具有抵消性。有了这个性质，就可以利用它对加入的向量进行修改。基本思路是：
       对于一个新加入的数字，从最高为考试往后扫，如果某一位该向量是1，但是之前的向量组中没有一个这一位是1，那么这一位就放如这个数字并且break；
       如果之前已经有该位为1的，那么该数字异或该位之前对应的数字。最后的结果是，新加入的数字x，要么被添加到某一个二进制位，
       要么变成0，说明这个数字对应的二进制向量不属于极大线性无关组。
      线性基构造完毕，我们就要求其极值。很多时候我们需要求一堆数字最大的异或和，这个时候就要用到线性基。线性基构造完毕之后，
      根据它的定义，任何线性基所张的向量空间的所有向量都能够表示为其线性组合。所以我们只需要找，这个线性基中最大的向量即可。
      做法就是，从高位开始取线性基的每一个基底，如果异或能够使得结果变大，那么就异或。同时，这个还支持有初始值的最大值，
      因为线性基可以表示所有的向量，所以即使有一个初始值也是能够一起计算最大值的。
        其他的话还有最小值，与最大值类似，只不过是从线性基的最低为开始，还有第K大，这些可以看这个链接 。
struct Linear_Basis
{
    LL b[63],nb[63],tot;
 
    void init()
    {
        tot=0;
        memset(b,0,sizeof(b));
        memset(nb,0,sizeof(nb));
    }
 
    bool ins(LL x)
    {
        for(int i=62;i>=0;i--)
            if (x&(1LL<<i))
            {
                if (!b[i]) {b[i]=x;break;}
                x^=b[i];
            }
        return x>0;
    }
 
    LL Max(LL x)
    {
        LL res=x;
        for(int i=62;i>=0;i--)
            res=max(res,res^b[i]);
        return res;
    }
 
    LL Min(LL x)
    {
        LL res=x;
        for(int i=0;i<=62;i++)
            if (b[i]) res^=b[i];
        return res;
    }
 
    void rebuild()
    {
        for(int i=62;i>=0;i--)
            for(int j=i-1;j>=0;j--)
                if (b[i]&(1LL<<j)) b[i]^=b[j];
        for(int i=0;i<=62;i++)
            if (b[i]) nb[tot++]=b[i];
    }
 
    LL Kth_Max(LL k)
    {
        LL res=0;
        for(int i=62;i>=0;i--)
            if (k&(1LL<<i)) res^=nb[i];
        return res;
    }
} LB;

一个物品有两个属性，a和b。现在有很多这样的物品，要求从中取任意个，使得取出的物品中，任意几个物品的属性a的异或和不为0，同时满足b的和最大。
        线性基经典题目，首先，满足b的和最大，所以显然要按照b进行排序，首先选取b大的。然后就是满足a的异或和不为0。这里根据线性基的性质，
        线性基里面任意几个基底的异或值不为0，所以只要能够成功添加入线性基里面的向量，都可以直接满足这个要求，把其对应b的值加入结果。
        一直尝试把所有的向量往线性基里面加，累积成功加入的b的值即可。
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<cstdlib>
#include<vector>
#include<map>
#include<queue>
#define LL long long
#define N 20010
using namespace std;
 
struct Linear_Basis
{
    LL d[63],p[63],tot;
 
    void init()
    {
        tot=0;
        memset(d,0,sizeof(d));
        memset(p,0,sizeof(p));
    }
 
    bool ins(LL x)
    {
        for(int i=62;i>=0;i--)
            if (x&(1LL<<i))
            {
                if (!d[i]) {d[i]=x;break;}
                x^=d[i];
            }
        return x>0;
    }
} LB;
 
struct node{LL a,b;} p[N];
int n;
 
bool cmp(node a,node b)
{
    return a.b>b.b;
}
 
int main()
{
	while(~scanf("%d",&n))
	{
		LB.init(); int ans=0;
		for(int i=1;i<=n;i++)
            scanf("%lld%lld",&p[i].a,&p[i].b);
        sort(p+1,p+1+n,cmp);
        for(int i=1;i<=n;i++)
            if (LB.ins(p[i].a)) ans+=p[i].b;
        printf("%d\n",ans);
	}
}
