#include<bits/stdc++.h>
#define loc
#define debu
using namespace std;

int buf[1000+5][1000+5];
int pre_sum[1000+5][1000+5];
int mx_r;

template<class T>

inline bool scan_d(T&ret){
    char c;int sgn;
    if(c=getchar(),c==EOF)  return 0;
    while(c!='-'&&c(<'0'||c>'9'))   c=getchar();
    sgn=(c=='-')?   -1:1;
    ret=(c=='-')?0:(c-'0');
    while(c=getchar(),c>='0'&&c<='9')   ret=ret*10+(c-'0');
    ret*=sgn;
    return 1;
}

bool is_ok(int mid){
    for(i=1,ans=1;i<=n;i++)
            for(j=1;j<=m;j++)
            {
                a[i][j]=a[i-1][j-1]-(a[i-1][j-1]>=1);
                while(i+a[i][j]<=n&&j+a[i][j]<=m&&s[i+a[i][j]][j+a[i][j]]-s[i-1][j+a[i][j]]-s[i+a[i][j]][j-1]+s[i-1][j-1]<=1)
                    a[i][j]++;
                ans=max(ans,a[i][j]);
            }

    return false;
}


void find_max_sqre(){
    for(int i=1;i<=M;i++){
        for(int j=1;j<=N;j++){
            pre_sum[i][j]=pre_sum[i-1][j]+pre_sum[i][j-1]-pre_sum[i-1][j-1];
            if(buf[i][j]==1)    pre_sum++;
        }
    }

    int mid;
    int low=1,high=1000;
    while(low<=high){
        mid=(low+high)>>1;
        if(is_ok(mid))  low=mid+1;
        else    high=mid-1;
    }
    mx_r=high;
}

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    int N,M;
    scan_d(N),scan_d(M);
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            scan_d(buf[i][j]);
        }
    }

    find_max_sqre();

}
