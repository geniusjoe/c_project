#include<bits/stdc++.h>
#define loca
#define debu
using namespace std;

const int MAXN=500010;

int buf[4];


int main() {

#ifdef local
    freopen("testdata.in", "r+", stdin);
    freopen("testdata.out", "w+", stdout);
#endif // local

    //ios::sync_with_stdio(false);

    string a,b,c;
    cin>>a>>b>>c;

    int a_val,b_val,c_val;

    a_val=b_val=c_val=0;

    if(a[1]=='s')   a_val+=100;
    else if(a[1]=='m')  a_val+=200;
    else if(a[1]=='p')  a_val+=300;

    a_val+=a[0]-'0';

    buf[1]=a_val;


    if(b[1]=='s')   b_val+=100;
    else if(b[1]=='m')  b_val+=200;
    else if(b[1]=='p')  b_val+=300;

    b_val+=b[0]-'0';

    buf[2]=b_val;


    if(c[1]=='s')   c_val+=100;
    else if(c[1]=='m')  c_val+=200;
    else if(c[1]=='p')  c_val+=300;

    c_val+=c[0]-'0';

    buf[3]=c_val;

    sort(buf+1,buf+1+3);

    if((buf[3]-buf[2]==1&&buf[2]-buf[1]==1&&buf[3]-buf[1]==2)
       ||(buf[1]==buf[2]&&buf[2]==buf[3]))
        cout<<0<<endl;
    else if(buf[3]-buf[2]==1||
            buf[2]-buf[1]==1||
            buf[3]-buf[1]==2||
            buf[2]-buf[1]==2||
            buf[3]-buf[2]==2||
            buf[2]==buf[1]
            ||buf[2]==buf[3]
            ||buf[1]==buf[3])
        cout<<1<<endl;
    else
        cout<<2<<endl;

}