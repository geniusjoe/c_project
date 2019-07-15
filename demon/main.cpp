#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

const int module=1e9+7;

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    ios::sync_with_stdio(false);

    int low,high;
    while(scanf("%d%d",&low,&high)&&low!=0){
        double res=0;
        for(int i=low;i<=high;i++){
            res+=pow(i,-2.0/3);
        }
        res*=1e-15*1/3;
        printf("%.5E\n",res);
    }



}
