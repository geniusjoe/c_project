#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

#define MAXM    500000+5

const int MAXN=500010;

int buf[MAXN],buf1[MAXN];
int max_len[MAXN];
int res[MAXN];

struct question{
    int l,r,type;
}questions[MAXN];

int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    int n,m;
    cin>>n>>m;

    for(int i=1;i<=m;i++){
        cin>>questions[i].type>>questions[i].l>>questions[i].r;
        if(questions[i].type==1){
            buf[questions[i].l]++;
            buf[questions[i].r]--;
        }
    }
    int tmp=0;
    for(int i=1;i<=n;i++){
        tmp+=buf[i];
        if(tmp>=1&&buf1[i]==0)  buf1[i]=0;
        else if(tmp==0)    buf1[i+1]=-1;
    }
    res[0]=10000;
    for(int i=1;i<=n;i++)   res[i]=res[i-1]+buf1[i];

    max_len[n]=n;
    for(int i=n-1;i>=1;i--)
    {
        if(res[i]<=res[i+1])    max_len[i]=max_len[i+1];
        else    max_len[i]=i;
    }

    bool flag=true;
    for(int i=1;i<=m;i++){
        if(questions[i].type==0&&max_len[questions[i].l]<questions[i].r)
            continue;
        else if(questions[i].type==1)   continue;
        else {
            flag=false;
            break;
        }
    }

    if(flag==true){
        cout<<"YES"<<endl;
        for(int i=1;i<=n;i++){
            cout<<res[i]<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"NO"<<endl;
    }


}
