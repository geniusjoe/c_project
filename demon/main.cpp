#include<bits/stdc++.h>
#define loc
#define debu
using namespace std;
long long big=4397400000000;

long long extend_gcd(long long a,long long b,long long &x,long long &y) {
    if(a==0&&b==0)
        return -1;
    if(b==0) {
        x=1;
        y=0;
        return a;
    }
    long long d=extend_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
long long m[10],a[10];
bool solve(long long &m0,long long &a0,long long m,long long a) {
    long long y,x;
    long long g=extend_gcd(m0,m,x,y);
    if(abs(a-a0)%g)
        return false;
    x*=(a-a0)/g;
    x%=m/g;
    a0=(x*m0+a0);
    m0*=m/g;
    a0%=m0;
    if(a0<0)
        a0+=m0;
    return true;
}
bool MLES(long long &m0,long long &a0,long long n) {
    bool flag=true;
    m0=1;
    a0=0;
    for(long long i=0; i<n; i++)
        if(!solve(m0,a0,m[i],a[i])) {
            flag=false;
            break;
        }
    return flag;
}


int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local
    int T;
    scanf("%d",&T);
    for(int j=1; j<=T; j++) {
        scanf("%I64d%I64d%I64d",&m[0],&m[1],&m[2]);
        scanf("%I64d%I64d%I64d",&a[0],&a[1],&a[2]);
        long long x,y;
        MLES(x,y,3);
        long long res=y;
        if(y==0) {
            printf("0\n");
            continue;
        }
        res=pow(y,1.0/3);
        if(res*res*res<y)   res++;
        printf("%I64d\n",res);
    }
}
