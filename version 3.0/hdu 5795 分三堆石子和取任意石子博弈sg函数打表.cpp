/// 题意: n堆石子，操作1，取任意数的式子，操作2，将一堆石子分成三堆非空石子
/// 求sg函数 
/// 打表代码，分堆的sg为 三个堆sg的抑或和
using namespace std;
int sg[1010]; int vis[1010];
int getsg(int x) {
    if(sg[x]!=-1) return sg[x];
    memset(vis,0,sizeof(vis));
    for(int i=1;i<x;i++) {
        int a=getsg(i);
        for(int j=1;j<x-i;j++) {
            int buf=a; int b=getsg(j); int c=getsg(x-i-j);
            buf^=b;buf^=c; vis[buf]=1;
        } vis[a]=1;
    }
    vis[0]=1;
    for(int i=1;;i++) { if(!vis[i]) return i; }
} 
int main() {
    memset(sg,-1,sizeof(sg));
    sg[0]=0,sg[1]=1,sg[2]=2;
    for(int i=0;i<1000;i++) {
        sg[i]=getsg(i); printf("sg[%d]=%d\n",i,sg[i]);
    }
}
#include<bits/stdc++.h>
using namespace std; 
 int getsg(int x) {
    if(x<=2) return x;
    else if(x%8==0) return x-1;
    else if(x%8==7) return x+1;
    else return x;
} 
int main() {
    int T,n; cin>>T;
    while(T--) {
        scanf("%d",&n); int cnt=0;
        for(int i=0;i<n;i++) {
            int buf; scanf("%d",&buf);
            cnt^=getsg(buf);
        }
        if(cnt!=0) printf("First player wins.\n");
        else printf("Second player wins.\n");
    }
}
