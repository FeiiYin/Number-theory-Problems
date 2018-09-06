#include<iostream>
#include<cmath>
#include<assert.h>
using namespace std;
typedef long long LINT;
LINT a,b,goal,n;
int mark[160000],prime[160000],e,bl[10000005];
LINT pn(int n)
{
    LINT s=LINT(n*(log(n)+log(log(n))-1)+n*(log(log(n))-2)/log(n)-6.0*n/1000.0);
    return s<=1?1:s;
}

inline LINT V2IDX(LINT v, LINT N, LINT Ndr, LINT nv) {
    return v >= Ndr ? (N/v - 1) : (nv - v);
}

LINT primesum(LINT N) {
    LINT *S;
    LINT *V;

    LINT r = (LINT)sqrt(N);
    LINT Ndr = N/r;

    assert(r*r <= N and (r+1)*(r+1) > N);

    LINT nv = r + Ndr - 1;

    V = new LINT[nv];
    S = new LINT[nv];

    for (LINT i=0; i<r; i++) {
        V[i] = N/(i+1);
    }
    for (LINT i=r; i<nv; i++) {
        V[i] = V[i-1] - 1;

    }

    for (LINT i=0; i<nv; i++) {
      //S[i] = V[i] * (V[i] + 1) / 2 - 1;若求素数和，使用此处
        S[i]=V[i] - 1;
      //若求素数个数使用此处
    }

    for (LINT p=2; p<=r; p++) {
        if (S[nv-p] > S[nv-p+1]) {
            LINT sp = S[nv-p+1];
            LINT p2 = p*p;
            for (LINT i=0; i<nv; i++) {
                if (V[i] >= p2) {
                //S[i] -= p* (S[V2IDX(V[i]/p, N, Ndr, nv)] - sp);若求素数和，使用此处
                    S[i] -= 1* (S[V2IDX(V[i]/p, N, Ndr, nv)] - sp);
                  //若求素数个数，使用此处
                } else {
                    break;
                }
            }
        }
    }

    return S[0];
}

int main()
{
    cin>>n;
    a=pn(n);
    if(a%2&&a>1)a=a-1;//防止预估值本身就是素数的情况，刚开始被这里坑了3个test
    b=a+7000000;
    goal=n-primesum(a);
    for(int i=2;i<=160000;i++)
    {
        if(!mark[i])
        {
            prime[++e]=i;
            for(LINT j=(LINT)i*i;j<=160000;j+=i)
            {
                mark[j]=1;
            }
        }
    }
    LINT xxx,c;
    for(int i=1;i<=e;i++)
    {
        xxx=(LINT)ceil(1.0*a/prime[i]);
        if(xxx==1) xxx++;
        for(LINT j=xxx;(c=j*prime[i])<b;j++)
        {
            bl[c-a]=1;
        }
    }
    int ans=0;
    c=b-a;
    if(a==1) ans--;
    for(int i=0;i<c;i++)
    {
        if(!bl[i]) ans++;
        if(ans==goal)
        {
            cout<<i+a<<endl;
            break;
        }
    }
    return 0;
}
