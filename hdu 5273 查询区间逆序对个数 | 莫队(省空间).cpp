/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int maxn=1e5+5;
const int maxm=1e5+5;
/*
    数范围比较大，离散化为[1,n]就好了
    数只有1000个，q次查询[l,r]之间的逆序对数
    如果[l,r]来求[l,r+1] 或[l,r-1]，只要统计a[i]的贡献就好了
    a[i]的贡献可以通过查询树状数组log2(1000)的时间内得到
    这种性质正适合莫队算法，总体复杂度O(n*sqrt(n)*log2(n)+q)
    可以很快的得到答案
    即使n<=1e5，也可以快速得到答案
*/

int a[maxn],b[maxn],c[maxn],d[maxn];
int block, n;
int ql[maxm],qr[maxm],qq[maxm],ans[maxm];

inline int lowbit(int x){return x&(-x);}
bool cmp1(int i,int j){return a[i]<a[j];}
void add(int x,int val){
    while(x<=n)c[x]+=val,x+=lowbit(x);
}
int query(int x){
    int res=0;
    while(x>0)res+=c[x],x-=lowbit(x);
    return res;
}

bool cmp2(int i,int j){
    int q1=ql[i]/block;
    int q2=ql[j]/block;
    if(q1!=q2)return q1<q2;
    if(qr[i]!=qr[j])return qr[i]<qr[j];
    return qr[i]<qr[j];
}

int main(){
    int q;    scanf("%d %d", &n, &q);
    block=sqrt(n);

    for(int i=1;i<=n;i++)scanf("%d", &a[i]), b[i]=i;
    sort(b+1, b+1+n, cmp1);

    int tot=0, last=-1;
    for(int i=1;i<=n;i++){
        if(a[b[i]]==last)d[b[i]]=tot;
        else d[b[i]]=++tot,last=a[b[i]];
    }

for(int i=0;i<q;i++)scanf("%d %d", &ql[i], &qr[i]),qq[i]=i;
    sort(qq,qq+q,cmp2);

    int l=1,r=1,res=0;
    add(d[1],1);
    for(int i=0;i<q;i++){
        int L=ql[qq[i]],R=qr[qq[i]];
        while(r<R){
            res+=r-l+1-query(d[r+1]);
            add(d[r+1],1);
            r++;
        }
        while(r>R){
            res-=r-l+1-query(d[r]);
            add(d[r],-1);
            r--;
        }
        while(l<L){
            res-=query(d[l]-1);
            add(d[l],-1);
            l++;
        }
        while(l>L){
            res+=query(d[l-1]-1);
            add(d[l-1],1);
            l--;
        }
        ans[qq[i]]=res;
    }
    for(int i=0;i<q;i++)
        printf("%d\n",ans[i]);
    return 0;
}
