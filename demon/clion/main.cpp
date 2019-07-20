#include<bits/stdc++.h>
using namespace std;

#define local

const int maxn=1000;

int buf[maxn][maxn];
int n;
long long ans;


void dfs(int x,int t,long long Sum) {
    if(x==n){
        ans=max(ans,Sum);
        return ;
    }
    if(t<n){

    }
    if(n-x>t){
        
    }

}

int main()
{
#ifdef local
    freopen("testdata.in","r+",stdin);
    freopen("testdata.out","w+",stdout);
    #endif

    ios::sync_with_stdio(false);
    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>buf[i][j];
        }
    }
    dfs(1,1,ans);
}